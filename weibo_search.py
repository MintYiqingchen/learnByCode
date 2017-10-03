#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2017-10-03 15:38:11
# @Author  : mintyi

import os
import requests, re

def search_word(word, number):
	'''
	返回某个关键词的查找结果，返回设置为number的结果数量
	'''
	def findEmoji(text):
		'''返回本条微博中所有的emoji情况'''
		pat = re.compile(r'\[(?P<emoji>[\u4e00-\u9fa5]+)\]') # 匹配中文的正则表达式
		match = pat.finditer(text)
		if match:
			result = ['[{}]'.format(m.group('emoji')) for m in match]
			print(result)
			return result
		else: 
			return None

	url = "https://weibo.cn/search/mblog"
	page = 1
	form = {
			'advancedfilter':1,
			'keyword':word,
			'hasori':1,
			'endtime':'20171003',
			'sort':'time',
			'page':page
	}
	# 到时候再加上动态cookie
	headers = {
				'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.79 Safari/537.36',
				'Referer': 'https://weibo.cn/search/mblog?advanced=mblog&f=s',
				'Cookie': '_T_WM=a5a430659dfef8b5a24a360a0a4cca3e; SUB=_2A25010skDeRhGedJ6lcW9S_Izz6IHXVUOFVsrDV6PUJbkdBeLVLgkW0Xl9c3wKIZqRwZuvUD8tQRF_XPDQ..; SUHB=0xnzbR1hdpUOt0; SCF=AgMX3dTsKV9vV0NaB3PAra9SmUNEr8fxOEhARyyt284bq-xLexvGW2MVs8QwbRBDi4YoRunSeRXz0m7r4ZSNmRM.; SSOLoginState=1507015540'	
	}
	'''
	for i in range(1,page+1):
		form['page']=i
		r = requests.get(url=url, params=form, headers = headers)
		content_list = findContent(r.text)
		for content in content_list:
			emojis = findEmoji(content)
	'''
	r = requests.get(url=url, params=form, headers = headers)
	emojis = findEmoji(r.text)
	return r
if __name__ == '__main__':
	r = search_word('emoji', 0)
	print(r.status_code)
	print(r.headers)
	with open('test.html','w',encoding = 'utf8') as f:
		f.write(r.text) 