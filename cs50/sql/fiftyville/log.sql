-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";
    --"Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse." 
    --"Interviews were conducted today with three witnesses who were present"
    --"at the time — each of their interview transcripts mentions the courthouse."

SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2020;
    --158|Jose|2020|7|28|“Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
    --159|Eugene|2020|7|28|“I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
    --160|Barbara|2020|7|28|“You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
    --161|Ruth|2020|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
    --162|Eugene|2020|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
    --163|Raymond|2020|7|28|As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
--RUTH: saw thief get into car and drive away in the courthouse parking lot, check footage.
--EUGENE: saw thief withdrawing money this morning, at atm at Fifer Street.
--RAYMOND: saw thief left build while talking to phone *less than a minute*. They'll leave the city with earliest flight tomorrow.

--1)Check RAYMOND: (saw thief left build while talking to phone *less than a minute*. They'll leave the city with earliest flight tomorrow.)
SELECT * FROM flights WHERE day = 29 AND month = 7 AND year = 2020 AND origin_airport_id =(SELECT id
FROM airports WHERE city = "Fiftyville");
    --18|8|6|2020|7|29|16|0
    --23|8|11|2020|7|29|12|15
    --36|8|4|2020|7|29|8|20
    --43|8|1|2020|7|29|9|30
    --53|8|9|2020|7|29|15|20
--Tomorrow earliest flight: 36|8|4|2020|7|29|8|20
SELECT * FROM passengers WHERE flight_id = 36;
    --36|7214083635|2A
    --36|1695452385|3B
    --36|5773159633|4A
    --36|1540955065|5C
    --36|8294398571|6C
    --36|1988161715|6D
    --36|9878712108|7A
    --36|8496433585|7B
SELECT * FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = 36);
--SUS:
    --395717|Bobby|(826) 555-1652|9878712108|30G67EN
    --398010|Roger|(130) 555-0289|1695452385|G412CB7
    --449774|Madison|(286) 555-6063|1988161715|1106N58
    --467400|Danielle|(389) 555-5198|8496433585|4328GD8
    --560886|Evelyn|(499) 555-9472|8294398571|0NTHK55
    --651714|Edward|(328) 555-1152|1540955065|130LD9Z
    --686048|Ernest|(367) 555-5533|5773159633|94KL13X
    --953679|Doris|(066) 555-9701|7214083635|M51FA04
--We have 8 suspects now. Lets move on.

--2)Check Eugene: (saw thief withdrawing money this morning, at atm at Fifer Street.)
SELECT * FROM atm_transactions 
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
    --246|28500762|2020|7|28|Fifer Street|withdraw|48
    --264|28296815|2020|7|28|Fifer Street|withdraw|20
    --266|76054385|2020|7|28|Fifer Street|withdraw|60
    --267|49610011|2020|7|28|Fifer Street|withdraw|50
    --269|16153065|2020|7|28|Fifer Street|withdraw|80
    --288|25506511|2020|7|28|Fifer Street|withdraw|20
    --313|81061156|2020|7|28|Fifer Street|withdraw|30
    --336|26013199|2020|7|28|Fifer Street|withdraw|35
--Lets check those bank accounts.
SELECT * FROM bank_accounts WHERE account_number IN(
SELECT account_number FROM atm_transactions 
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw");
    --49610011|686048|2010
    --26013199|514354|2012
    --16153065|458378|2012
    --28296815|395717|2014
    --25506511|396669|2014
    --28500762|467400|2014
    --76054385|449774|2015
    --81061156|438727|2018
               --ID--
--Now check those ID's.
SELECT * FROM people WHERE id IN(
SELECT person_id FROM bank_accounts WHERE account_number IN(
SELECT account_number FROM atm_transactions 
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
--SUS:
    --395717|Bobby|(826) 555-1652|9878712108|30G67EN
    --396669|Elizabeth|(829) 555-5269|7049073643|L93JTIZ
    --438727|Victoria|(338) 555-6650|9586786673|8X428L0
    --449774|Madison|(286) 555-6063|1988161715|1106N58
    --458378|Roy|(122) 555-4581|4408372428|QX4YZN3
    --467400|Danielle|(389) 555-5198|8496433585|4328GD8
    --514354|Russell|(770) 555-1861|3592750733|322W7JE
    --686048|Ernest|(367) 555-5533|5773159633|94KL13X
--We have 8 suspects now. Lets move on to the last info.

--3)Check Ruth: (saw thief get into car and drive away in the courthouse parking lot, check footage.)
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND activity = "exit";
    --There are bunch of info here. Let's move on for now. 
    -- !!! TODO

--4)Check Raymond: (saw thief left build while talking to phone *less than a minute*. They'll leave the city with earliest flight tomorrow.)
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60;
--SUS:
    --221|(130) 555-0289|(996) 555-8899|2020|7|28|51
    --224|(499) 555-9472|(892) 555-8872|2020|7|28|36
    --233|(367) 555-5533|(375) 555-8161|2020|7|28|45
    --234|(609) 555-5876|(389) 555-5198|2020|7|28|60
    --251|(499) 555-9472|(717) 555-1342|2020|7|28|50
    --254|(286) 555-6063|(676) 555-6554|2020|7|28|43
    --255|(770) 555-1861|(725) 555-3243|2020|7|28|49
    --261|(031) 555-6622|(910) 555-3251|2020|7|28|38
    --279|(826) 555-1652|(066) 555-9701|2020|7|28|55
    --281|(338) 555-6650|(704) 555-2131|2020|7|28|54
--Let's find out whose phone numbers.
SELECT * FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60);
    --395717|Bobby|(826) 555-1652|9878712108|30G67EN
    --398010|Roger|(130) 555-0289|1695452385|G412CB7
    --438727|Victoria|(338) 555-6650|9586786673|8X428L0
    --449774|Madison|(286) 555-6063|1988161715|1106N58
    --514354|Russell|(770) 555-1861|3592750733|322W7JE
    --560886|Evelyn|(499) 555-9472|8294398571|0NTHK55
    --561160|Kathryn|(609) 555-5876|6121106406|4ZY7I8T
    --686048|Ernest|(367) 555-5533|5773159633|94KL13X
    --907148|Kimberly|(031) 555-6622|9628244268|Q12B3Z3


--Let's bind some info now.
--Intersect first sus and 2nd sus.
SELECT * FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = 36)
INTERSECT
SELECT * FROM people WHERE id IN(
SELECT person_id FROM bank_accounts WHERE account_number IN(
SELECT account_number FROM atm_transactions 
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
    --395717|Bobby|(826) 555-1652|9878712108|30G67EN
    --449774|Madison|(286) 555-6063|1988161715|1106N58
    --467400|Danielle|(389) 555-5198|8496433585|4328GD8
    --686048|Ernest|(367) 555-5533|5773159633|94KL13X
--We have 4 sus left. Let's intersect the phone calls now.

SELECT * FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60)
INTERSECT
SELECT * FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = 36)
INTERSECT
SELECT * FROM people WHERE id IN(
SELECT person_id FROM bank_accounts WHERE account_number IN(
SELECT account_number FROM atm_transactions 
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));

    --395717|Bobby|(826) 555-1652|9878712108|30G67EN
    --449774|Madison|(286) 555-6063|1988161715|1106N58
    --686048|Ernest|(367) 555-5533|5773159633|94KL13X
--3 suspects left!
--Now go back and check courthouse_security_logs!

SELECT * FROM courthouse_security_logs 
WHERE year = 2020 AND month = 7 AND day = 28 AND license_plate = "30G67EN" OR license_plate = "1106N58" OR license_plate = "94KL13X";
    --232|2020|7|28|8|23|entrance|94KL13X --Ernest
    --237|2020|7|28|8|34|entrance|1106N58 --Madison
    --261|2020|7|28|10|18|exit|94KL13X --Ernest
    --268|2020|7|28|10|35|exit|1106N58 --Madison
SELECT * FROM people WHERE phone_number = "(375) 555-8161";
    --864400|Berthold|(375) 555-8161||4V16VO0
--Ernest, came to courthouse at 8:23 and left 10:18. Called Berthold.
SELECT * FROM people WHERE phone_number = "(676) 555-6554";
    --250277|James|(676) 555-6554|2438825627|Q13SVG6
--Madison, came to courthouse at 8:34 and left 10:35. Called James.

--Let's Take a look at Ernest and Madison ATM transactions:
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND account_number =(SELECT account_number FROM bank_accounts WHERE person_id = 686048);
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND account_number =(SELECT account_number FROM bank_accounts WHERE person_id = 449774);
    --267|49610011|2020|7|28|Fifer Street|withdraw|50 (Ernest)
    --266|76054385|2020|7|28|Fifer Street|withdraw|60 (Madison)

SELECT * FROM airports WHERE id = 4;
        --4|LHR|Heathrow Airport|London
    
    --IF theif is Ernest, Berthold helped him;
    --IF theif is Madison, James helped him;
    --They both going to London Tomorrow.

SELECT * FROM people WHERE name = "Berthold";
    --864400|Berthold|(375) 555-8161|NO PASSPORT|4V16VO0
SELECT * FROM people WHERE name = "James";
    --250277|James|(676) 555-6554|2438825627|Q13SVG6
--Eighter James or Berthold purchased the flight ticket.

    --449774|Madison|(286) 555-6063|1988161715|1106N58
        --250277|James|(676) 555-6554|2438825627|Q13SVG6
    --686048|Ernest|(367) 555-5533|5773159633|94KL13X
        --864400|Berthold|(375) 555-8161|---|4V16VO0

SELECT * FROM courthouse_security_logs WHERE license_plate = "4V16VO0" AND day = 28 AND month = 7;
--248|2020|7|28|8|50|entrance|4V16VO0 --Berthold
--249|2020|7|28|8|50|exit|4V16VO0
SELECT * FROM courthouse_security_logs WHERE license_plate = "Q13SVG6" AND day = 28 AND month = 7;
--Nothing.

SELECT * FROM interviews WHERE name = "Berthold" OR name = "Ernest" OR name = "James" OR name = "Madison";
    --26|James|2020|2|5|“The circumstances are of great delicacy, and every precaution has to be taken to quench what might grow to be an immense scandal and seriously compromise one of the reigning families of Europe. To speak plainly, the matter implicates the great House of Ormstein, hereditary kings of Bohemia.”
    --79|Madison|2020|4|8|“Quite an interesting study, that maiden,” he observed. “I found her more interesting than her little problem, which, by the way, is rather a trite one. You will find parallel cases, if you consult my index, in Andover in ’77, and there was something of the sort at The Hague last year. Old as is the idea, however, there were one or two details which were new to me. But the maiden herself was most instructive.”
--nothing useful.


SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";
    --"Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse." 
    --"Interviews were conducted today with three witnesses who were present"
    --"at the time — each of their interview transcripts mentions the courthouse."

    --- DAMN I missed the Time information! theft took place at 10:15 AM!
    --- RUTH SAID: Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot 
    --and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

    -- SO they time frame of the courthouse_security_logs must be ~ 10.20 AM!
    -- IT'S Ernest and Berthold helped him, he flight to London!