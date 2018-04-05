import numpy as np
import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

#Rank, VmRSS(status), VmSize,  Rss(smaps), Pss, Ppid, pVmRSS(status), pVmSize,  pRss(smaps), pPss
data = pd.read_csv('memory_info.csv', sep=',')
print data

#mean/std of mpi process pss
pss_mean = np.mean(data["Pss"])
pss_std = np.std(data['Pss'])

#mean/std of parent pss
pPss_mean = np.mean(data["pPss"])
pPss_std = np.std(data['pPss'])

print "Mpi process mean: ", pss_mean, "std: ", pss_std, "max: ", np.max(data['Pss']), "min: ", np.min(data['Pss'])
print "Daemon mean: ", pPss_mean, "std: ", pPss_std, "max: ", np.max(data['pPss']), "min: ", np.min(data['pPss'])

#find outliers with range 0.1*mean
for index, row in data.iterrows() :
    if abs(row['Pss'] - pss_mean) > (pss_mean * 0.1):
        print "Outlier Mpi process Rank/Pss", row['Rank'],row['Pss']
    if abs(row['pPss'] - pPss_mean) > (pPss_mean * 0.1):
        print "Outlier Daemon Rank/Pss", row['Rank'],row['pPss']

plt.figure()
plt.ylabel('Mpi process memory usage(KB)', fontsize=14, color='blue')
plt.xlabel('Mpi Rank', fontsize=14, color='blue')
#red dashes, blue squares
#plt.plot(data["Pss"], 'r--', data["pPss"], 'bs')
plt.plot(data["Rank"], data["Pss"], 'rs')
plt.savefig('Mpi_process_pss.pdf')

plt.figure()
data.boxplot(column=["Pss"])
plt.savefig('Mpi_process_pss_boxplot.pdf')

plt.figure()
plt.ylabel('Daemon memory usage(KB)', fontsize=14, color='blue')
plt.xlabel('Mpi Rank', fontsize=14, color='blue')
#red dashes, blue squares
plt.plot(data["Rank"],data["pPss"], 'rs')
plt.savefig('Daemon_pss.pdf')

plt.figure()
data.boxplot(column=["pPss"])
plt.savefig('Daemon_pss_boxplot.pdf')
