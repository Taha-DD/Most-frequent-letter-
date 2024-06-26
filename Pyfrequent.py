from collections import Counter

most, frequency = max(Counter(str(input("Enter a string: "))).items(), key=lambda x: x[1])

print(f"The most frequent letter is \"{most}\" with {frequency} appearing times")