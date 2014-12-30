#!/usr/bin/env python
# -*- coding: utf-8 -*-
# make_data.py
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
	'tower_pangu',
	'tower_houyi',
	'tower_leizhenzi',
	'tower_shuange'
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
		'main': {},
		'star': {},
		'code': {
			'code': {},
			'star': {
				'1':{'len': 0},
				'2':{'len': 0},
				'3':{'len': 0},
				'4':{'len': 0},
				'5':{'len': 0}
			}
		}
	}

	##############################
	# 工作表 main
	table = data.sheet_by_name(u'main')

	for r in range(2,table.nrows):
		result['main'][table.cell_value(r,2)] = table.cell_value(r,3)

	##############################
	# 工作表 star
	table = data.sheet_by_name('star')
	
	for r in range(3,table.nrows):
		row = {}
		row['star'] = table.cell_value(r,1)
		ccbi_map = {
			'1': table.cell_value(r,2),
			'2': table.cell_value(r,3),
			'3': table.cell_value(r,4)
		}
		row['ccbi'] = ccbi_map
		row['skill'] = {}
		
		for c in range(5,8):
			if table.cell_value(r,c) != xlrd.XL_CELL_EMPTY and table.cell_value(r,c) != '':
				row['skill'][table.cell_value(r,c)] = {}
		
		row[table.cell_value(2,8)] = table.cell_value(r,8);
		
		result['star'][int(table.cell_value(r,1))] = row
	
	##############################
	# 工作表 code
	table = data.sheet_by_name('code')
	
	for r in range(3,table.nrows):
		row = {}
		row['code'] = table.cell_value(r,1)
		att_map = {
			'1': table.cell_value(r,8),
			'2': table.cell_value(r,9),
			'3': table.cell_value(r,10)
		}
		row['att'] = att_map
		
		frq_map = {
			'1': table.cell_value(r,11),
			'2': table.cell_value(r,12),
			'3': table.cell_value(r,13)
		}
		row['frq'] = frq_map
		
		range_map = {
			'1': table.cell_value(r,14),
			'2': table.cell_value(r,15),
			'3': table.cell_value(r,16)
		}
		row['range'] = range_map
		
		attn_map = {
			'1': table.cell_value(r,17),
			'2': table.cell_value(r,18),
			'3': table.cell_value(r,19)
		}
		row['attn'] = attn_map
		
		cost_map = {
			'1': table.cell_value(r,20),
			'2': table.cell_value(r,21),
			'3': table.cell_value(r,22)
		}
		row['cost'] = cost_map
		
		recy_map = {
			'1': table.cell_value(r,23),
			'2': table.cell_value(r,24),
			'3': table.cell_value(r,25)
		}
		row['recy'] = recy_map
		
		if table.ncols > 26:
			if table.cell_value(2,26) != xlrd.XL_CELL_EMPTY and table.cell_value(2,26) != '':
				para1_map = {
					'1': table.cell_value(r,26),
					'2': table.cell_value(r,27),
					'3': table.cell_value(r,28)
				}
				row['para1'] = para1_map
				
		if table.ncols > 29:
			if table.cell_value(2,29) != xlrd.XL_CELL_EMPTY and table.cell_value(2,29) != '':
				para2_map = {
					'1': table.cell_value(r,29),
					'2': table.cell_value(r,30),
					'3': table.cell_value(r,31)
				}
				row['para2'] = para2_map
		
		if table.ncols > 32:
			if table.cell_value(2,32) != xlrd.XL_CELL_EMPTY and table.cell_value(2,32) != '':
				row[table.cell_value(2,32)] = table.cell_value(r,32)
				row[table.cell_value(2,33)] = table.cell_value(r,33)
		
		if table.ncols > 34:
			if table.cell_value(2,34) != xlrd.XL_CELL_EMPTY and table.cell_value(2,34) != '':
				para3_map = {
					'1':table.cell_value(r,34),
					'2':table.cell_value(r,35),
					'3':table.cell_value(r,36)
				}
				row['skill_limit'] = para3_map
		
		result['code']['code'][int(table.cell_value(r,1))] = row
		
		for c in range(2,7):
			if table.cell_value(r,c) != xlrd.XL_CELL_EMPTY and table.cell_value(r,c) != '':
				result['code']['star'][str(c-1)][int(table.cell_value(r,c))] = {'code': table.cell_value(r,1)}
				result['code']['star'][str(c-1)]['len'] += 1
				
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
	
##############################
# 自动更新资源文件
os.system("python make_data_enemy.py")
os.system("python make_data_hero.py")
os.system("python make_data_skill.py")
os.system("python make_data_wave.py")
os.system("python resources.py")