import time

start = time.strptime("1 1 1901", "%d %m %Y")
print(time.strftime("%A (#%w), week %W, %d %b (%m) %Y", start))

numsun = 0
for year in range(1901, 2001):
  for month in range(1, 13):
    if int(time.strftime("%w", time.strptime("1 " + str(month) + " " + str(year), "%d %m %Y"))) == 0: numsun += 1
print(numsun)