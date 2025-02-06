import json
import random
random.seed(40)
with open('./file/service(int).json', 'r') as f:
    first = json.load(f)

first_service = first['services']

numbers = []
temps = []
length = len(first_service)
for i in range(45):
    for j in range(16):
     random_number = random.randint(0, length-1)
     print('random_number',random_number)
     for index in range(len(first_service[random_number])):
         temps.append(first_service[random_number][index])
    print('temps',temps)
    numbers.append(temps)
    temps = []

print(numbers)
print("len",len(numbers))
result_dict = {"users": numbers}

print(len(result_dict['users']))

with open('file/geolife/users(geolife)_45.json', 'w') as outfile:
    json.dump(result_dict, outfile)