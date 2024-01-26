# Importing Packages
import random #Package/Library for random number generator functions
import csv #To Export to CSV File

# Start of Program
rows=3
cols=9
rowcount=5
tickets=[[0 for i in range(cols)] for j in range(rows)] 

# Assigning Slots for filling 15 numbers
unused_col=list([0]*cols)
unused_col_overall=list(range(cols))
for i in range(rows-1):
    unused_col=list(range(cols))
    used_col=[]
    while(len(used_col)<rowcount):
        t=random.choice(unused_col)
        if t not in used_col:
            used_col.append(t)
            unused_col.remove(t)
            tickets[i][t]=1
            if t in unused_col_overall:
                unused_col_overall.remove(t)
unused_col=list(range(cols))
used_col=unused_col_overall
del unused_col_overall
for i in used_col:
    tickets[rows-1][i]=1
while(len(used_col)<rowcount):
    t=random.choice(unused_col)
    if t not in used_col:
        used_col.append(t)
        unused_col.remove(t)
        tickets[rows-1][t]=1

# Print Assigned Slots for the Ticket
print("\nAssigned Slots\n")
for row in tickets:
    for i in row:
        print(f'{i:^4}',end=" ")
    print()

# Filling Numbers
for i in range(cols):
    if i==0:
        ranlist=list(range(1,10))
    elif i==-1:
        ranlist=list(range(11))
    else:
        ranlist=list(range(10))
    fills= [j for j in range(rows) if tickets[j][i]==1]
    ranlist_used=[]
    while(len(ranlist_used)<=len(fills)):
        t=random.choice(ranlist)
        if t not in ranlist_used:
            ranlist_used.append(t)
            ranlist.remove(t)
    ranlist_used=sorted(ranlist_used)
    for j in range(len(fills)):
        tickets[fills[j]][i]=10*i+ranlist_used[j]

# Print Final Ticket
print("\nFinal Ticket\n")
for row in tickets:
    for i in row:
        print(f'{i:^4}',end=" ")
    print()
print()

# Export to CSV File
text=[]
text+=["New Ticket"]
with open('Tickets.csv', 'a', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(text)
    writer.writerows(tickets)
    writer.writerows(' ')