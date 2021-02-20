import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database

        name = request.form.get('name')
        month = request.form.get('month')
        day = request.form.get('day')

        id = db.execute("SELECT MAX(id) FROM birthdays")
        id = id[0]['MAX(id)'] + 1

        db.execute("INSERT INTO birthdays VALUES(?, ?, ?, ?)", id, name, month, day)

        # TODO: make some error checks. Make sure name-month and day are valid.

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html

        people = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", people=people)


