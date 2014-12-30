#!/usr/bin/env python
# -*- coding: utf-8 -*-
# make_data_wave.py
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
	'wave_01_01'
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
		'main': [
			{'wave_id': 0}
		]
	}
	
	##############################
	# 工作表 main
	table = data.sheet_by_name(u'main')

	wave_id = ''
	wave_item = {}
	for r in range(3, table.nrows):
		
		cell_value = table.cell_value(r, 1)
		if (cell_value != '' and cell_value != wave_id): # 是新的skill
			if wave_id != '':
#				result['main'][int(wave_id)] = wave_item
				result['main'].append(wave_item)
				
			wave_id = cell_value
			wave_item = {
				table.cell_value(2, 1): wave_id,
				table.cell_value(2, 2): table.cell_value(r, 2),
				table.cell_value(2, 3): table.cell_value(r, 3),
				'sub_wave_map': {}
			}
		
		##############################
		# 填充一个row
		row = {}
		for c in range(4, 12):
			key = table.cell_value(2, c)
			value = table.cell_value(r, c)
			row[key] = value
		wave_item['sub_wave_map'][int(table.cell_value(r, 4))] = row		
		if (r == table.nrows - 1):
#			result['main'][int(wave_id)] = wave_item
			result['main'].append(wave_item)
		
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