#!/usr/bin/env python
# -*- coding: utf-8 -*-
# make_data_enemy.py
# Author: Wang-Yichun

import sys
reload(sys)
sys.setdefaultencoding('utf8')

import xlrd
import json
import os

# 
# 输入路径
input_path = 'data_input'
# 输出路径
output_path1 = '../Assets/Assets/Data'
output_path2 = 'data_output'

# 注册文件名
file_name_list = [
	'enemy'
]

# 每次处理一个文件
for file_name in file_name_list:
    ##############################
	# 准备工作
	xlsx_full_file_name = input_path + '/' + file_name + ".xlsx"
	json_full_file_name1 = output_path1 + '/' + file_name + ".json"
	json_full_file_name2 = output_path2 + '/' + file_name + ".json"

	data = xlrd.open_workbook(xlsx_full_file_name)
	
	##############################
	# 整体框架
	result = {
		'main': {}
	}
	
	##############################
	# 工作表 main
	table = data.sheet_by_name(u'main')

	for r in range(3, table.nrows):
		row = {}
		for c in range(1, table.ncols):
			key = table.cell_value(2,c)
			value = table.cell_value(r,c)
			row[key] = value;
			
		result['main'][table.cell_value(r,2)] = row
	
	##############################
	# 输出到json文件
	if not os.path.isdir(output_path1):
		os.makedirs(output_path1)
	
	if not os.path.isdir(output_path2):
		os.makedirs(output_path2)
		
	f = open(json_full_file_name1, 'w')
	f.write(json.dumps(result, ensure_ascii=False))
	f = open(json_full_file_name2, 'w')
	f.write(json.dumps(result, ensure_ascii=False))

	print xlsx_full_file_name + " -> " + json_full_file_name1 + " == Successful.."