# -*- coding: utf-8 -*-
"""
Created on Mon May 21 20:49:26 2018

@author: zhongqi
"""

import os

path = 'F:/Work/市场/培训/专业技能分享/Python培训/exec/'

#for i in os.walk(path) :
#    print(i)
    
def traverse(f):
    fs = os.listdir(f)
    for f1 in fs:
        tmp_path = os.path.join(f,f1)
        if not os.path.isdir(tmp_path):
            print('文件: %s'%tmp_path)
        else:
            print('文件夹：%s'%tmp_path)
            traverse(tmp_path)
              
#path = 'F:/source_files/python/'  
traverse(path)  