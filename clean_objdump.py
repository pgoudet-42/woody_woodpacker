import sys

def main(file):
    with open(file) as f:
        line = f.readline()
        while line:
            str = ""
            for i, c in enumerate(line):
                if i > 9 and i < 32:
                    if c == "\n":
                        break
                    str += c
                    if c == " " and line[i + 1].isspace() == False:
                        str += "0x"
            print(str)
            line = f.readline()


if __name__ == "__main__":
    main(sys.argv[1])