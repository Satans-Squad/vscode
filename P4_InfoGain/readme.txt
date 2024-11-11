outlook,temp,humidity,wind,play
sunny,hot,high,weak,no
sunny,hot,high,strong,no
overcast,hot,high,weak,yes
rain,mild,high,weak,yes
rain,cool,normal,weak,yes
rain,cool,normal,strong,no
sunny,mild,high,weak,no
sunny,cool,normal,weak,yes


- take input as vector of Data (map<string,string>), storing each tuple and key value pair of each column

- create a function which returns map<string,double> info gain of non target attribute

    - iterate over the first row and run gain function for non-target attributes

        - find frequency of all the values present for that particular attribute 

        - loop over the freq map    
            - loop over the data rows
            - collect the rows where data[attr]=freq.first
            (basically rows with particular value)

            - calc probability=size of subset / size of data

            - subsetEntropy=prob*entropy(subset,target)
        
        - calculate dataset entropy
        - return datasetEntropy-subsetEntropy;