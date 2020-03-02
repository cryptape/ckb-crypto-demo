# -*- coding: utf-8 -*-

import random,hashlib,json,string


def sha256(input):
    return  hashlib.sha256(input.encode()).hexdigest()

def ranstr(num):
    return ''.join(random.sample(string.ascii_letters + string.digits, num))



with  open("testcase","w") as f:
    testcase = []
    testcase.append(["test",sha256("test")])
    testcase.append([sha256("test"),sha256(sha256("test"))])

    for i in range(2,1000):
        input = ranstr(random.randint(0,50))
        output = sha256(input)
        testcase.append([input,output])

    json.dump(testcase,f,indent=4)
