//
// Created by tim on 2020/2/28.
//

#ifndef UNTITLED3_SHA256_TEST_H
#define UNTITLED3_SHA256_TEST_H

#endif //UNTITLED3_SHA256_TEST_H


struct testcase{
    char * in;
    char * out;
};

testcase  testlist[] = {

        {
                "test",
                "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08"
        },
        {
                "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08",
                "7b3d979ca8330a94fa7e9e1b466d8b99e0bcdea1ec90596c0dcc8d7ef6b4300c"
        },
        {
                "yO9PgCXt",
                "1b7e39eafd731c98da08df71f7d9cbdf70b9da676afff18e85c551a787cb2f59"
        },
        {
                "k6xapigw9nFmrqyhuS8",
                "bde29452925679dee339b0a85d001b3577ca23618edd8c60bb4664362be36e79"
        }
        }
