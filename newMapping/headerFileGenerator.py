import re
# This doesn't include struct 
headerText = "#pragma once \n\n"
pattern = "^[a-z#].*"
count = 0
filename = "car"
x = 0
with open(filename + ".c", encoding='utf8') as f:
    for line in f:
        if((re.match(pattern, line) and "main" not in line and "struct" not in line and "enum" not in line)) :
            if(line[0] != "#" and count == 0):
                count+=1
                headerText += "\n\n"
    
            headerText += (line.replace("{",";\n"))
                
print(headerText)
with open(filename + ".h", 'w') as f:
    f.write(headerText)