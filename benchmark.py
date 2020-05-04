"""
Creation of graphics
"""
import pandas
import seaborn
import sys
from matplotlib import pyplot


def main():
    """
    Main function
    """
    from_file, to_file = sys.argv[1:]

    dataframe = pandas.read_csv(from_file)
    seaborn.lmplot(x='expr_len', y='time', hue="parser", data=dataframe,
                   truncate=True, height=8, aspect=1.2)
    pyplot.xlim(0, 20)
    pyplot.xticks(range(0, 20))
    pyplot.yticks(range(0, 30))
    # pyplot.yscale("log")
    pyplot.grid(True)
    # pyplot.show()
    pyplot.savefig(to_file)


if __name__ == "__main__":
    main()
