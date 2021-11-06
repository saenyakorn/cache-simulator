import matplotlib.pyplot as plt 
# direct
direct_x = [] # 4 numbers
direct_y4 =  [] # 4 numbers
direct_y8 =  [] # 4 numbers
direct_y16 = [] # 4 numbers
direct_y32 = [] # 4 numbers
# asso
asso_x = [] # 6 numbers
asso_LRU2 = [] # 6 numbers
asso_RR2 =  [] # 6 numbers
asso_LRU4 = [] # 6 numbers
asso_RR4 =  [] # 6 numbers
fig, direct = plt.subplots()
fig, asso = plt.subplots()

direct.set_xscale('log', basex=2)
direct.plot(direct_x, direct_y4, label='Block Size 4 Bytes', color='#EB5757')
direct.plot(direct_x, direct_y8, label='Block Size 8 Bytes', color='#F2C94C')
direct.plot(direct_x, direct_y16, label='Block Size 16 Bytes', color='#219653')
direct.plot(direct_x, direct_y32, label='Block Size 32 Bytes', color='#2F80ED')
direct.legend()
direct.title.set_text('Direct mapped')
direct.set_xlabel('Cache Size (KB)')
direct.set_ylabel('Miss Rate')

asso.set_xscale('log', basex=2)
asso.plot(asso_x, asso_LRU2, label='LRU 2-way', color='#EB5757')
asso.plot(asso_x, asso_RR2, label='RR 2-way', color='#F2C94C')
asso.plot(asso_x, asso_LRU4, label='LRU 4-way', color='#219653')
asso.plot(asso_x, asso_RR4, label='RR 4-way', color='#2F80ED')
asso.legend()
asso.title.set_text('Associativity')
asso.set_xlabel('Cache Size (KB)')
asso.set_ylabel('Miss Rate')

plt.show()