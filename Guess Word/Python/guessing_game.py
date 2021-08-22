def guess_my_word(word):
    if (word == "apple"):
        return True;
    else:
        return False;


def main():
    condition = False;
    print("Try to guess my word: ")
    while(1 and condition == False):
        x = input()
        condition = guess_my_word(x)
        if(condition == False):
            print("Bzzzz... Wrong. Try again!")            
        else:
            print("Correct! You are awesome!")

if __name__ == "__main__":
    main()
