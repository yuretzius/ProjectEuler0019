import time

# some rather confusing explanations: https://en.wikipedia.org/wiki/Doomsday_rule

# month's doomsday shift
# determined as follows:
# in March the first doomsday is the 7th
# (since February 28 or 29 is always a doomsday, and it is like 0th March)
# so 7 - 7 = 0
# for the even months there is the rule 4/4, 6/6, 8/8, 10/10, 12/12
# so April's shift 7 - 4 = 3, June's 7 - 6 = 1, Aug 7 - (8 - 7) = 6
# Oct 7 - (10 - 7) = 4, Dec 7 - (12 - 7) = 2.
# for odd month a mnemonic "I work 9 to 5 in 7 - 11"
# 9/5 and 5/9
# May's shift 7 - (9 - 7) = 5, Sept 7 - 5 = 2
# 11/7 and 7/11
# July 7 - (11 - 7) = 3, Nov 7 - 7 = 0
# January and February are special cases 
# because of the leap years, but if we treat them as the last months of
# the previous year, then as Dec 26 is a doomsday, 26+7 = Dec 33 = Jan 2
# Jan's shift is 7 - 2 = 5
# And then 2+7+7+7+7 = Jan 30 is a doomsday, so Feb 6 is one too, and
# Feb's shift 7 - 6 = 1. Done!  

t = (5, 1, 0, 3, 5, 1, 3, 6, 2, 4, 0, 2)

def findDay(day, month, year) :
        if month < 3: year -= 1 # same doomsday works from March to February, otherwise have to bother with leap years
        
        # anchor day for the century
        century = year// 100 # in this calculation "century" is just the first 2 digits of the year
        anchor = 2 + 5*(century % 4) % 7
        print("century's anchor:", anchor)
        
        # determine the drift day for this year
        year %= 100 # two-digit year
        yodd = int(year % 2 != 0) # 1 if odd, 0 if even
        year = (year + 11*yodd) // 2
        yodd = int(year % 2 != 0) # 1 if odd, 0 if even
        drift = 7 - (year + 11*yodd) % 7 # drift of the day of the week for this year
        print("year's drift:", drift)
        doomsday = (anchor + drift)%7
        print("year's doomsday:", doomsday)
        print("month's doomsday shift:", t[month-1])
        w = (doomsday + t[month-1] + day) % 7
        # 0 means Sunday
        return w   
    
print("weekday as a num:", findDay(25, 12, 2027))


# what can one do with python's date|time strings
# table of all possible format codes and examples: https://www.geeksforgeeks.org/python/python-time-strptime-function/

d = time.strptime("25 12 2027", "%d %m %Y")
print(time.strftime("weekday as a word: %A, weekday as a num: %w, week#: %W, day: %d, month as a word: %b, month as a num: %m, year: %Y", d))

