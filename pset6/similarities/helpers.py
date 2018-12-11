from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    # TODO
    # Take in string input a, b
    # Split each string into lines
    # Compute list of all lines appearing in both a and b
    # Return the list

    listA = set(a.split("\n"))
    listB = set(b.split("\n"))

    return listA & listB


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO
    # Take in string input a, b
    # Split each string into sentences
    # Compute list of all sentences appearing in both a and b
    # Return the list
    # from nltk.tokenize import
    sentencesA = set(sent_tokenize(a))
    sentencesB = set(sent_tokenize(b))

    return sentencesA & sentencesB


def get_all_substring(string, n):
    substrings = []

    for i in range(len(string) - n + 1):
        substrings.append(string[i: i + n])

    return substrings


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # TODO
    # Take in string input a, b and lenght of substring
    # Split each string into each substring
    # Compute list of all substring appearing in both a and b
    # Return the list
    substringsListA = set(get_all_substring(a, n))
    substringsListB = set(get_all_substring(b, n))

    return substringsListA & substringsListB
