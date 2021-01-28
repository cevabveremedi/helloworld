let userScore = document.getElementById("user-score");
let compScore = document.getElementById("comp-score");
let status = document.getElementById("status");
let rock = document.getElementById("r");
let paper = document.getElementById("p");
let scissors = document.getElementById("s");

function main()
{
    rock.addEventListener("click", function(){
        game("r");
    })
    paper.addEventListener("click", function(){
        game("p");
    })
    scissors.addEventListener("click", function(){
        game("s");
    })
}

function game(userChoice)
{
    compChoice = comp();
    let winner = ["pr", "rs", "sp"];
    for(let i = 0; i < 3; i++)
    {
        c = compChoice + userChoice;
        u = userChoice + compChoice;
        if(!winner[i].localeCompare(c))
        {
            return lose(userChoice, compChoice);
        }
        if(!winner[i].localeCompare(u))
        {
            return win(userChoice, compChoice);
        }
    }
    return tie(userChoice, compChoice);
}

function comp()
{
    let x = Math.floor(Math.random() * 3);
    let ch = ["r", "p", "s"];
    return ch[x];
}

function win(userChoice, compChoice)
{
    document.getElementById(userChoice).classList.add("buttonWin");
    setTimeout(() => {
        document.getElementById(userChoice).classList.remove("buttonWin");
    }, 1500);
    userScore.innerText++;
    status.innerText = `${actual(userChoice)} beats ${actual(compChoice)}, you won!`
}

function lose(userChoice, compChoice)
{
    document.getElementById(userChoice).classList.add("buttonLose");
    setTimeout(() => {
        document.getElementById(userChoice).classList.remove("buttonLose");
    }, 1500);
    compScore.innerText++;
    status.innerText = `${actual(userChoice)} loses ${actual(compChoice)}, you lost!`
}

function tie(userChoice, compChoice)
{
    document.getElementById(userChoice).classList.add("buttonTie");
    setTimeout(() => {
        document.getElementById(userChoice).classList.remove("buttonTie");
    }, 1500);
    status.innerText = `${actual(userChoice)} equals to ${actual(compChoice)}, tie!`
}

function actual(name)
{
    if(name == "r")
    {
        return "rock";
    }
    else if(name == "p")
    {
        return "paper";
    }
    return "scissors";
}

main();