import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Select all symbol and shares that the owner owns from portfolio table
    portfolioDatas = db.execute("SELECT symbol, shares FROM portfolio WHERE id=:id", id=session["user_id"])

    # create a temp to store total worth of cash and shares
    totalCash = 0

    # update each symbol prices and total
    for portfolioData in portfolioDatas:
        symbol = portfolioData["symbol"]
        shares = portfolioData["shares"]
        # Look up for the newest price when user checks the index page
        quote = lookup(symbol)
        # Get all the total shares of same symbol and update by using the newest stock price
        total = shares * quote["price"]
        totalCash += total
        # Update stock price and total cash in database by usering user ID and symbol
        db.execute("UPDATE portfolio SET price=:price, total=:total WHERE id=:id AND symbol=:symbol", price=usd(quote["price"]) , total=usd(total) , id=session["user_id"], symbol=symbol)

    # Get users cash amount. (Not stock shares)
    cashInHand = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])

    # update total cash -> cash and shares worth
    totalCash += cashInHand[0]["cash"]

    # print profilo in index page
    updatedPortfolio = db.execute("SELECT * FROM portfolio WHERE id=:id", id=session["user_id"])

    return render_template("index.html", stocks=updatedPortfolio, cash=usd(cashInHand[0]["cash"]), total=usd(totalCash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")
    else:
        # check proper number of shares
        if not request.form.get("quote"):
            return apology("must provide symbol")
        else:
            quote = lookup(request.form.get("quote"))

        if not quote:
            return apology("Symbol Invailded")

        # check the user input shares its a vailded int
        try:
            shares = int(request.form.get("shares"))
            if shares < 0:
                return apology("share(s) must be positive number")
        except:
            return apology("invailed share(s)")

        # select users cash from db by using cookie
        userCash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        #check if enough money to
        #or float(money[0]["cash"])?
        if not userCash or float(userCash[0]["cash"]) < quote["price"] * shares:
            return apology("Not enough money")

        # update history
        db.execute("INSERT INTO 'transaction' ('symbol', 'shares', 'price', 'id') VALUES(:symbol, :shares, :price, :id)", symbol=quote["symbol"], shares=shares, price=usd(quote["price"]), id=session["user_id"])

        # update user cash
        db.execute("UPDATE users SET cash = cash - :purchase WHERE id = :id", purchase=quote["price"] * float(shares), id=session["user_id"])

        # select users symbol from db
        userShares = db.execute("SELECT shares FROM portfolio WHERE id = :id AND symbol=:symbol", id=session["user_id"], symbol=quote["symbol"])

        # if the symbol doesnt exist then create a new stock object
        if not userShares:
            db.execute("INSERT INTO portfolio (name, shares, price, total, symbol, id) VALUES(:name, :shares, :price, :total, :symbol, :id)",
                       name=quote["name"], shares=shares ,price=usd(quote["price"]), total=usd(shares * quote["price"]), symbol=quote["symbol"], id=session["user_id"])

        # Else if symbol exist then add the share
        else:
            shareTotal = userShares[0]["shares"] + shares
            db.execute("UPDATE portfolio SET shares=:shares WHERE id=:id AND symbol=:symbol",
                       shares=shareTotal, id=session["user_id"], symbol=quote["symbol"])

        # return to index
        return redirect(url_for("index"))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    histories = db.execute("SELECT * FROM 'transaction' WHERE id=:id", id=session["user_id"])

    return render_template("history.html", histories=histories)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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
        if not request.form.get("quote"):
            return apology("must provide symbol")
        else:
            quote = lookup(request.form.get("quote"))
            chart = request.form.get("https://api.iextrading.com/1.0/stock/aapl/chart/1d")

        if not quote:
            return apology("Symbol Invailded")
        else:
            return render_template("display.html", symbolValues=quote, chart=chart)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password was submitted
        elif request.form.get("password-confirm") != request.form.get("password"):
            return apology("confirmation password doesn't match", 403)

        # hash the password
        # Insert username with SQL Queries
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                    username=request.form.get("username"),
                    hash=generate_password_hash(request.form.get("password")))


        # check if username exisit, because usernames are UNIQUE field in the db
        if not result:
            return apology("username already exist")

        # If register is successfully, log them in auto
        # Remember which user has logged in
        session["user_id"] = result

        # Redirect user to home page

        return redirect(url_for("index"))
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
       # check proper number of shares
        if not request.form.get("quote"):
            return apology("must provide symbol")
        else:
            quote = lookup(request.form.get("quote"))

        if not quote:
            return apology("Symbol Invailded")

        # check the user input shares its a vailded int
        try:
            sharesToSell = int(request.form.get("shares"))
            if sharesToSell < 0:
                return apology("share(s) must be positive number")
        except:
            return apology("invailed share(s)")

        # check if enough shares to sell
        if sharesToSell <= 0:
            return apology("You have enter an invailded number.")

        userShares = db.execute("SELECT shares FROM portfolio WHERE id=:id AND symbol=:symbol", id=session["user_id"], symbol=quote["symbol"])

        if userShares[0]["shares"] < sharesToSell:
            return apology("You have enter an invailded number or you don't have enough shares to sell.")

        # update history database about the sells
        db.execute("INSERT INTO 'transaction' ('symbol', 'shares', 'price', 'id') VALUES(:symbol, :shares, :price, :id)", symbol=quote["symbol"], shares=-sharesToSell, price=usd(quote["price"]), id=session["user_id"])


        # update user cash
        userCash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        newUserCash = float(userCash[0]["cash"]) + (quote["price"] * int(sharesToSell))

        db.execute("UPDATE users SET cash=:newUserCash WHERE id=:id", id=session["user_id"], newUserCash=newUserCash)

        # update shares count
        totalShares = userShares[0]["shares"] - sharesToSell

        # if its 0 then delete the share from portfolio database
        if totalShares <= 0:
            db.execute("DELETE FROM portfolio WHERE id=:id AND symbol=:symbol", id=session["user_id"], symbol=quote["symbol"])
            return redirect(url_for("index"))

        # otherwise update the counts
        else:
            db.execute("UPDATE portfolio SET shares=:shares WHERE id=:id AND symbol=:symbol", shares=totalShares, id=session["user_id"], symbol=quote["symbol"])

            return redirect(url_for("index"))
    else:
         # Look up for all the stock(symbol) that user have.
        symbols = db.execute("SELECT symbol FROM portfolio WHERE id=:id", id=session["user_id"])

        return render_template("sell.html", symbols=symbols)

def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
