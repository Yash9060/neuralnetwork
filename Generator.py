# This is a generator file.
# This file helps in generating training data
# which is stored in a 'train_data.data' output file
# you can directely use that file in your program
# This is randomly generated input file

# Prasanna K Patil

# The goal of this file was to generate random inputs 
# which can be taken as training data for learning of
# Neural Networks.
# This file generates random input data for teaching neural network tables.

from random import randint

f = open("train_data.data", "w")
pairs=7 # denotes Number of pairs to be generated
lines = list()
oput = list()
for j in xrange(0,20):
    oput.append('0')
iput = ['0','0','0','0','0','0','0','0','0']
for i in range(pairs):
    a = randint(1,9)
    #b = randint(1,9)
    #while a==b :
        #b = randint(1,9)
    iput[a-1]='1'
    #iput[b-1]='1'
    lines.append(' '.join(iput))
    oput[(a*2)-1] = '1'
    lines.append(' '.join(oput))
    iput[a-1]='0'
    #iput[b-1]='0'
    oput[(a*2)-1]='0'

f.write('\n'.join(lines))
f.close()
print 'done'
