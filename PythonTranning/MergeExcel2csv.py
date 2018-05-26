# -*- coding: utf-8 -*-
"""
Created on Fri May 25 14:40:46 2018

@author: zhongqi
"""

# -*- coding: utf-8 -*-
"""
Created on Fri May 25 13:42:28 2018

@author: zhongqi
"""

import sys

import xlwt, xlrd
import csv

#from xlrd import open_workbook
#from xlwt import Workbook, easyxf

input_file1 = 'F:/Test-Data/PSD实战案例/2018经侦比武/杭州比武/智器云数据对接/目标文件：26万商户基础数据(有充值、提现、差额) - 副本.xlsx'
input_file2 = 'F:/Test-Data/PSD实战案例/2018经侦比武/杭州比武/智器云数据对接/26万商户数据（有邀请人ID） - 副本.xlsx'
input_file3 = 'F:/Test-Data/PSD实战案例/2018经侦比武/杭州比武/智器云数据对接/96万商家（有邀请人姓名、身份证） - 副本.xlsx'
#target_file = 'F:/Test-Data/PSD实战案例/2018经侦比武/杭州比武/智器云数据对接/Result.xlsx'

target_file = 'Result-M.csv'

#input_file1 = 'C:/Users/zhongqi/Documents/火眼金睛/样例数据/QQdata-1.xls'

key1 = ('序号', '商家ID', '会员ID', '对应用户', '商户身份证号', '用户电话', '商铺名称', '商铺地址', '开户行', '银行账号', '省', '市', '区、县', '地区ID', '负责人ID', '负责人名称', '负责人身份证号', '负责人开户银行', '负责人银行卡号', '现金账户', '累计现金账户', '银果账户（货款剩余）', '累计收银果账户（货款）', '货款现金账户', '累计货款现金账户', '计赠送银果金额', '累计收入金额（订单总金额）', '充值', '提现', '差额')
#key1 = ('会员ID','') # !! 不能定义为：key1 = ('会员ID') 否则会当成字符数组来处理
key2 = ('会员Id','邀请人Id')
key3 = ('会员Id','邀请人姓名', '邀请人身份证号')

firstLine=[]


#for col in key11:
#    for c in key1:  
##        print(c, col)             
#        if col == c:
#            print('标题', col)   
#            

# 从Excel文件中提取指定的列内容            
def extractFile(sheetSrc, colNames):
  
    data = []
    print('Sheet名称', sheetSrc.name, '有', sheetSrc.nrows, '行', sheetSrc.ncols, '列')
    title_index = [] # 需要提取列的名称
    for row_index in range(sheetSrc.nrows):
        newRowList=[]

        if row_index==0:   
            # 读取标题行，记录需要提取列的索引
            for col_index in range(sheetSrc.ncols):
                strContent=str(sheetSrc.cell_value(row_index, col_index))   
                firstLine.append(strContent)
                for col in colNames:                 
                    if col == strContent:
                        title_index.append(col_index)
                        
#            print('    标题', firstLine)     
#            print('    目标标题', colNames)    
#            print('    标题索引', title_index)
#            return data
        else:
            # 开始提取内容，放入data
            for col_index in (title_index):
                
                if sheetSrc.cell_type(row_index, col_index)==2:
                    strContent=str(int(sheetSrc.cell_value(row_index, col_index)))
                else:
                    strContent=str(sheetSrc.cell_value(row_index, col_index))
                
#                    types += ' ' + str(sheet.cell_type(row_index, col_index))
                newRowList.append(strContent.strip())
        
#                types.strip(' ')
#                newRowList.append(types)
#                print(newRowList)

        data.append(newRowList)

    return data
    
# end def extractFile            
      

# 将list转换为Dict

def convert2Dict(data):
    
    dictData={}
    
    for d in (data):
        for v in d:
            if dictData.get(v)==None:
                value =[]
                for i in range(len(d)):
                    if i != 0:
                        value.append(d[i])
                        
                dictData[d[0]] = value
#    
#            else:
#                print(d)

    return dictData
    
# 拼接列字段
# dictDataSrc和dataDst通过key来关联
# 从dictDataSrc中取出colNames内容，放入dataDst数据中
def mergeDataWithKey(dataDst, dictDataSrc, key, colNames):
    
    outData=[]
    newRow=[]

    for row in dataDst:
        newRow=row
        
        for i, v in enumerate(row):    
#            print(v)
            if i == 2:
                if dictDataSrc.get(v)!=None:
                    for d in dictDataSrc.get(v):
                        newRow.append(d)
                else:
                    for i in range(len(colNames)):
                        newRow.append('')
#        print(newRow)        
        outData.append(newRow)                  
                    
    return outData
#end def mergeDataWithKey


# 写Csv文件
def writeCsvFile(titles, data):
    
    with open(target_file, 'w', encoding='utf8', newline='') as file_writer:
        csv_writer = csv.writer(file_writer, delimiter=',')
        csv_writer.writerow(titles)
    
        for d in data:
            csv_writer.writerow(d)

    print('文件写入完成，共计', len(data), '行')        
# end def writeCsvFile

       
# sheetSrc1和sheetSrc2通过key来关联
# 从sheetSrc1取colNames1列，从sheetSrc2取colNames2列，组成新的csv文件outCsvFile
#def mergeSheetWithKey(outCsvFile, sheetSrc1, sheetSrc2, key, colNames1, colNames2):
    

# sheet.cell_type(row_index, col_index)
# ctype : 0 empty,1 string, 2 number, 3 date, 4 boolean, 5 error  

#for i, input_file in enumerate(fileList):
#with open(target_file, 'w', encoding='utf8', newline='') as file_writer:
#    csv_writer = csv.writer(file_writer, delimiter=',')


data1 = []
data2 = []
data3 = []

with xlrd.open_workbook(input_file1) as workbook:
    print('第1个文件有', workbook.nsheets, '个工作蒲') 
    for sheet in workbook.sheets():
        data1 = extractFile(sheet, key1)
print(len(data1))


with xlrd.open_workbook(input_file2) as workbook:
    print('第2个文件有', workbook.nsheets, '个工作蒲') 
    for sheet in workbook.sheets():
        data2 = extractFile(sheet, key2)
print(len(data2))

dictData = convert2Dict(data2)
key = '会员Id'
colNames = ('邀请人Id')
mergeDataWithKey(data1, dictData, key, colNames)

titles = list(key1)
titles.append('邀请人Id')

writeCsvFile(titles, data1)


#with xlrd.open_workbook(input_file3) as workbook:
#    print('第3个文件有', workbook.nsheets, '个工作蒲') 
#    for sheet in workbook.sheets():
#        data3 = extractFile(sheet, key3)
#print(len(data3))    
    

print('End...')


