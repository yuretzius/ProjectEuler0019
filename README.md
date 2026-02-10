# ProjectEuler0019
My work on

[problem #19 of projecteuler.net](https://projecteuler.net/problem=19):

Counting Sundays

You are given the following information, but you may prefer to do some research for yourself.

* 1 Jan 1900 was a Monday.
* Thirty days has September,<br>
April, June and November.<br>
All the rest have thirty-one,<br>
Saving February alone,<br>
Which has twenty-eight, rain or shine.<br>
And on leap years, twenty-nine.
* A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?

Completed on Sun, 21 Feb 2021, 12:20

#######################################################################################<br>
Please note: Project Euler's policy allows publication of solutions for the first 100 problems,
that's why I am sharing my work here for reference and educational purposes.
#######################################################################################<br>

One way of doing this is simple. Just use python's date/time libraries, e.g. time.
Here's a simple demo:

```python
d = time.strptime("25 12 2027", "%d %m %Y")
print(time.strftime("weekday as a word: %A, weekday as a num: %w, week#: %W, day: %d, month as a word: %b, month as a num: %m, year: %Y", d))
```

E.g. at Geeks for Geeks one can find [a comprehensive table of format codes and more examples](https://www.geeksforgeeks.org/python/python-time-strptime-function/).

Of course, this is no fun at all, so let's dive down into a more esoteric art of finding the day of the week. I am following [the Doomsday rule with odd 11 modification](https://en.wikipedia.org/wiki/Doomsday_rule). The algorithm here is for the Gregorian calendar. It can be modified to follow the Julian one, but with different values. 

Turns out, for each year one can define a constant "doomsday", which is the day of the week that every year happens on the same dates.

To figure the doomsday for the given year, one has to know the "anchor" for the current century. For the purpose of this algorithm "century" means just the two first digits of the year, so year 2000 is in the "20th" century, as well as 2026. Each century has a fixed anchor, for the current century it is Tuesday or 2 (the weekdays are counted starting from Sunday, and the value of Sunday is 0). For an arbitrary century the anchor can be determined as follows:

```python
century = year// 100
anchor = 2 + 5*(century % 4) % 7
```
E.g. for 19XX it is 3 or Wednesday. Once we know the anchor, we need to find out the "drift" for the year in question. That's where the "odd 11" rule comes in:

```python
year %= 100 # two-digit year
yodd = int(year % 2 != 0) # 1 if odd, 0 if even
year = (year + 11*yodd) // 2
yodd = int(year % 2 != 0) # 1 if odd, 0 if even
drift = 7 - (year + 11*yodd) % 7 
```
E.g. for 2026, it is even, but 26/2 is odd, so the drift 7 - (13 + 11)%7 = 4. Combining the century's anchor and the year's drift (modulo 7 if necessary) we get the doomsday for this year: 2 + 4 = 6, it is Saturday. 

The first easy-to-remember reference doomsday of each year is "the 0th of March", which is either February 28 or 29. Thus the first doomsday in March is March 7.
For the even months (except February) the rule is $n/n$ : 4/4, 6/6, 8/8 (or 1/8), 10/10 (or 3/10), and 12/12 (or 5/12). For the odd months except January and March the rule is "I work 9 to 5 at 7 - 11": 9/5 (or 2/5), 5/9, 11/7 (or 4/7), and 7/11. January and February, if we want to use current year's doomsday, are tricky because of the possibility of the leap shift. So it is much more convenient to start the year on March 1 and use the previous year's doomsday for January and February. Then they are fixed and the first ones fall on January 2 and February 6. For the coding purposes it is easiest to record these dates as a handy table of "month's shift", by subtracting the first doomsday of each month from 7: 5 for January, 1 for February, 0 for March, 3 for April etc.

```python
mshift = (5, 1, 0, 3, 5, 1, 3, 6, 2, 4, 0, 2)
```
Now all we need is to combine the values of doomsday, month's shift and the day of the month modulo 7. For example for May 25, 2026: doomsday, as we've already established, is Saturday, month's shift is 5, so the result: (6 + 5 + 25)%7 = 1, it is Monday. 

FindDay both in python and C++ are just day finding demonstrations (both with doomsday rule and in addition date tools in python), and Euler19 is actually solving the problem of counting Sundays, in C++ the beginning and end dates can be anything. Euler19.py just uses python's date tools, and Euler19 implements the doomsday rule.  