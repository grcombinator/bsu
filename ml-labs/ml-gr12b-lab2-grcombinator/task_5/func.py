def is_triangle(a,b,c):
    if a<=0 or b<=0 or c<=0:
        return False
    mx = max(a,b,c)
    if mx == a:
        if a>=b+c:
            return False
        return True
    elif mx == b:
        if b>=a+c:
            return False
        return True
    else:
        if c>=a+b:
            return False
        return True
        