def code_une_(lettre):
    a = ord(lettre) - 65
    return a

def decode_une_(carac):
    a = chr(65 + carac)
    return a

def decode_mot(Liste):
    b = list(map(decode_une_,Liste))
    b = "".join(b)
    return b

def cesar(phrase,decimal):
    L = []
    B = []
    for i in phrase:
        a = code_une_(i) + decimal
        if code_une_(i) == -33 :
            e = code_une_(i) + 33
            L.append(e)
        else :
            L.append(a)
    for i in L :
        if i == 0 :
            B.append(-33)
        else :
            b = i%26
            B.append(b)
    c = decode_mot(B)
    return c

def decesar(Phrase,decimal):
    L = []

    a = code_mots(Phrase)

    for i in a:
        if i == -33:
            L.append(-33)
        else:
            b = (i - decimal) % 26
            L.append(b)
    return decode_mot(L)

print(cesar("KYV RIK FW GIFXIRDDZEX ZJ KYV RIK FW FIXREZQZEX TFDGCVOZKP",9))



