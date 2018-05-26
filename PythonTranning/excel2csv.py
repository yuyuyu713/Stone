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

input_file1 = 'F:/Test-Data/PSD实战案例/2018经侦比武/杭州比武/智器云数据对接/26万商户数据（有邀请人ID）.xlsx'
#input_file2 = 'F:/Test-Data/PSD实战案例/2018经侦比武/杭州比武/智器云数据对接/96万商家（有邀请人姓名、身份证）.xlsx'
#input_file3 = 'F:/Test-Data/PSD实战案例/2018经侦比武/杭州比武/智器云数据对接/目标文件：26万商户基础数据(有充值、提现、差额).xlsx'
#target_file = 'F:/Test-Data/PSD实战案例/2018经侦比武/杭州比武/智器云数据对接/Result.xlsx'

#input_file1 = 'C:/Users/zhongqi/Documents/火眼金睛/样例数据/QQdata-1.xls'
input_file2 = 'C:/Users/zhongqi/Documents/火眼金睛/样例数据/QQdata-2.xls'
input_file3 = 'C:/Users/zhongqi/Documents/火眼金睛/样例数据/QQdata-3.xls'
target_file = 'Result.csv'

fileList = (input_file1, input_file2, input_file3)
titles = ['QQ号码', '好友QQ号', 'QQ昵称', '好友昵称']


#workbook_new = xlwt.Workbook()
#sheet_new = workbook_new.add_sheet('sheet1', True)
#
#rowIndex=0
#
#def writeOneRow(sheetName, rowIndex, data):
#    for i, t in enumerate(data):
#        sheetName.write(rowIndex, i, t)

# sheet.cell_type(row_index, col_index)
# ctype : 0 empty,1 string, 2 number, 3 date, 4 boolean, 5 error  

#for i, input_file in enumerate(fileList):
with open(target_file, 'w', encoding='utf8', newline='') as file_writer:
    csv_writer = csv.writer(file_writer, delimiter=',')
    with xlrd.open_workbook(input_file1) as workbook:
        print('第1个文件有', workbook.nsheets, '个工作蒲') 
        for sheet in workbook.sheets():
            print('    Sheet名称', sheet.name, '有', sheet.nrows, '行', sheet.ncols, '列')
            for row_index in range(sheet.nrows):
                newRowList=[]
#                types=''
                for col_index in range(sheet.ncols):
                    if sheet.cell_type(row_index, col_index)==2:
                        strContent=str(int(sheet.cell_value(row_index, col_index)))
                    else:
                        strContent=str(sheet.cell_value(row_index, col_index))
                        
#                    types += ' ' + str(sheet.cell_type(row_index, col_index))
                    newRowList.append(strContent.strip())
                
#                types.strip(' ')
#                newRowList.append(types)
#                print(newRowList)
                csv_writer.writerow(newRowList)
                    
                if row_index==0:
                    print('    标题名称', newRowList)                   
##                    writeOneRow(sheet_new, rowIndex, newRowList)
##                    rowIndex += 1
#                elif row_index <= 60000:
#                    writeOneRow(sheet_new, rowIndex, newRowList)
#                    rowIndex += 1
                        


       
print('End...')