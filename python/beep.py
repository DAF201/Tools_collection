import random
import winsound
duration = 1000
while (1):
    frequency = random.randrange(37, 32767)
    winsound.Beep(frequency, duration)
