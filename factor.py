#faster factors
def factors(num):
    def is_prime(x):
        if (x == 2) or (x == 3):
            return True
        if (x % 6 != 1) and (x % 6 != 5):
            return False
        for i in range(5, int(x ** 0.5) + 1, 6):
            if (x % i == 0) or (x % (i + 2) == 0):
                return False
        return True

    if is_prime(num):
        return(1, num)
    else:
        start = int(pow(num, 0.5))
        if start < num-start:
            while(num % start != 0):
                start -= 1
            return (start, int(num/start))
        else:
            while(num % start != 0):
                start += 1
            return (start, int(num/start))
