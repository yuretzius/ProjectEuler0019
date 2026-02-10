import time

numsun = 0
for year in range(1901, 2001):
  for month in range(1, 13):
    if int(time.strftime("%w", time.strptime("1 " + str(month) + " " + str(year), "%d %m %Y"))) == 0: numsun += 1
print(numsun)