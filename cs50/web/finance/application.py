# export API_KEY=pk_a84231df04d14836bb4867725dbd7449

import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/remove", methods=["GET", "POST"])
@login_required
def removeAccount():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for current user
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Ensure password is correct
        if not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("wrong password", 403)

        # Delete user from database
        db.execute("DELETE FROM history WHERE user_id = ?", session["user_id"])
        db.execute("DELETE FROM users WHERE id = ?", session["user_id"])
        session.clear()
        # Redirect user to home page
        flash("Account deleted permanently.")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("delete.html")

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT symbol, SUM(shares) AS total FROM history WHERE user_id=:id GROUP BY symbol HAVING total > 0", id=session["user_id"])
    history = []
    wealth = 0
    for row in rows:
        stock = lookup(row["symbol"])
        history.append({
            "symbol": stock["symbol"],
            "name": stock["name"],
            "shares": row["total"],
            "price": usd(stock["price"]),
            "value": usd(stock["price"] * row["total"])
        })
        wealth += float(stock["price"] * row["total"])
    try:
        user_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        user_cash = user_cash[0]['cash']
    except IndexError:
        user_cash = 10000
    wealth += user_cash

    return render_template("index.html", history=history, user_cash=usd(user_cash), wealth=usd(wealth))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        try:
            shares = int(shares)
        except:
            return apology("shares must be integer")

        if shares <= 0:
            return apology("shares must be positive")

        company = lookup(symbol.upper())
        if not company:
            return apology("Invalid symbol")

        total = float(company['price']) * int(shares)
        user_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        user_cash = user_cash[0]['cash']

        if total > user_cash:
            return apology("Can't Afford")

        # Update the user cash
        user_cash -= total
        db.execute("UPDATE users SET cash=:user_cash WHERE id=:id", user_cash=user_cash, id=session["user_id"])

        # Update the history of this
        db.execute("INSERT INTO history (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=symbol, shares=shares, price=company["price"])

        flash("Bought!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM history WHERE user_id=:id", id=session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)

        result = lookup(symbol.upper())
        if not result:
            return apology("Invalid symbol")
        return render_template("quoteres.html", pholder={
            'name': result['name'],
            'symbol': result['symbol'],
            'price': usd(result['price'])
        })
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirm = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not confirm:
            return apology("must confirm your password", 400)

        # Ensure passwords are match
        elif not password == confirm:
            return apology("passwords don't match")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username don't exists
        if len(rows) != 0:
            return apology("username already exist", 400)

        # Insert new user
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=generate_password_hash(password))

        # Remember which user has logged in
        session.clear()
        session["user_id"] = db.execute("SELECT * FROM users WHERE username = ?", username)[0]["id"]

        # Redirect user to home page
        flash("Registered!")
        return redirect("/")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if not symbol:
            return apology("must provide symbol")
        if not shares:
            return apology("must provide shares")

        stock = lookup(symbol)
        if not stock:
            return apology("Invalid symbol")

        rows = db.execute("SELECT symbol, SUM(shares) AS total FROM history WHERE user_id=:id GROUP BY symbol HAVING total > 0", id=session["user_id"])

        for row in rows:
            if row["symbol"] == symbol:
                if row["total"] < shares:
                    return apology("Too many shares")

                # Update the user cash
                total = float(stock['price']) * int(shares)
                user_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
                user_cash = user_cash[0]['cash']
                user_cash += total
                db.execute("UPDATE users SET cash=:user_cash WHERE id=:id", user_cash=user_cash, id=session["user_id"])

                # Update the history of this
                db.execute("INSERT INTO history (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=symbol, shares=-shares, price=stock["price"])

                flash("Sold!")
        return redirect("/")
    else:
        options = db.execute("SELECT symbol, SUM(shares) AS total FROM history WHERE user_id=:id GROUP BY symbol HAVING total > 0", id=session["user_id"])
        return render_template("sell.html", options=options)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
