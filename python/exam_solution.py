
# coding: utf-8

# In[14]:



import datetime  # use this module to deal with dates:  https://docs.python.org/3/library/datetime.html


class PostcardList(): 
    def __init__(self):
		# File name from which the postcards were taken.
        self._file = ""
		# List of postcards read from file.
        self._postcards = []
		# A dictionary date,index for all postcard dates.
        self._date = {}
		# A dictionary string, index for all postcard senders.
        self._from = {}
		# A dictionary string, index for all postcard receivers.
        self._to = {}
    def readFile(self,file_name):
        self._file=file_name
        with open(file_name,'r') as f:
            for i in f:
                self._postcards.append(i)
        f.close()
        self.parsePostcards()
    def writeFile(self,filename): 
        f = open(filename, 'w')
        for line in self._postcards:
            f.write(line)
        f.close()
    def parsePostcards(self):
        
            for i in range(0, len(self._postcards)):
                date, sender, receiver = self._postcards[i].split(" ")
                # Remove extra characters from strings.
                date = date[5:15]
                sender = sender[5:-1]
                receiver = receiver[3:-2]
                date = datetime.datetime.strptime(date, "%Y-%m-%d")
                if date not in self._date:
                    self._date[date] = []
                self._date[date].append(i)
                if sender not in self._from:
                    self._from[sender] = []
                self._from[sender].append(i)
                if receiver not in self._to:
                    self._to[receiver] = []
                self._to[receiver].append(i)
                
        
            
            
    def getNumberOfPostcards(self):
        return len(self._postcards)

    def updateFile(self,filename):
        f=open(filename, "a") 
        for line in self._postcards:
            f.write(line)
        f.close()    
    def updateLists(self, filename):
        self._file = filename
        for line in open(self._file, "r"):
            self._postcards.append(line)
        f.close()
        self.parsePostcards()
    def getPostcardsByReceiver(self, receiver):#check if the key of two is the same passed then it appends it to  letters and then return it as list
        letters=[]
        if receiver in self._to:
            for i in self._to[receiver]:
                letters.append(self._postcards[i])
        return letters
            
    
    def getPostcardsBySender(self, sender):
        letters=[]
        if sender in self._from:
            for i in self._from[sender]:            
                    letters.append(self._postcards[i])
        return letters
    
    def getPostcardsByDateRange(self,date_range):
        letters = []			
        keys=sorted(list(self._date.keys()))
        for date in keys:
            if( date >= date_range[0] and date <= date_range[1] ):
                for i in self._date[date]:
                    letters.append(self._postcards[i])
        return letters


