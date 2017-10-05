#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2017-10-03 15:38:11
# @Author  : mintyi

import os
import requests, re, csv
from bs4 import BeautifulSoup
import datetime

def findContent(soup):
	'''
	获得微博用户动态
	'''
	items = soup.find_all('div',class_ = 'c',id=True)
	timepat = re.compile(r'\d{1,2}月\d{1,2}日 \d{1,2}:\d{1,2}')
	result = []
	for item in items:
		cct = item.select('.ctt')[0].get_text()[1:] # 内容
		result.append(cct)
	return result
def writeRow(sheet, row, rownum):
	'''将一行写到sheet中去'''
	if rownum >= 1000:
		sheet.flush_row_data()
	for i in range(len(row)):
		sheet.write(rownum, i, row[i])
def search_word(word, starttime, endtime):
	'''
	返回某个关键词的查找结果，返回设置为number的结果数量
	'''
	def findEmoji(text):
		'''返回本条微博中所有的emoji情况'''
		pat = re.compile(r'\[(?P<emoji>[\u4e00-\u9fa5]+)\]') # 匹配中文的正则表达式
		match = pat.finditer(text)
		result = ['[{}]'.format(m.group('emoji')) for m in match]
		if len(result)==0:
			return None
		else: 
			print(result)
			return list(set(result))

	url = "https://weibo.cn/search/mblog"
	headers = {
				'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.79 Safari/537.36',
				'Referer': 'https://weibo.cn/search/mblog?advanced=mblog&f=s',
				'Cookie': '_T_WM=a5a430659dfef8b5a24a360a0a4cca3e; SUB=_2A25010skDeRhGedJ6lcW9S_Izz6IHXVUOFVsrDV6PUJbkdBeLVLgkW0Xl9c3wKIZqRwZuvUD8tQRF_XPDQ..; SUHB=0xnzbR1hdpUOt0; SCF=AgMX3dTsKV9vV0NaB3PAra9SmUNEr8fxOEhARyyt284bq-xLexvGW2MVs8QwbRBDi4YoRunSeRXz0m7r4ZSNmRM.; SSOLoginState=1507015540'	
	}

	form = {
			'advancedfilter':1,
			'keyword':word,
			'hasori':1,
			'starttime':None,
			'endtime':None,
			'sort':'time',
			'page':None
	}
	itemCount = 0

	row0 = [u'时间',u'关键词',u'表情',u'内容']
	csvf = open('weibo.csv','a',encoding='utf8', newline='')
	writer = csv.writer(csvf)
	writer.writerow(row0)

	while(starttime<=endtime):
		form['starttime'] = starttime.strftime('%Y%m%d')
		form['endtime'] = starttime.strftime('%Y%m%d')
		page = 1
		while(True):
			form['page']=page
			r = requests.get(url=url, params=form, headers = headers)
			soup = BeautifulSoup(r.text, 'lxml')
			content_list = findContent(soup)
			for content in content_list:
				emojis = findEmoji(content)
				if emojis: # 如果存在表情，进行累计条目，存储该条
					emojis = ','.join(emojis)
					writer.writerow((form['starttime'], word, emojis, content))
			page += 1
			if page>100:
				break

		starttime = starttime + datetime.timedelta(1)
	return r
if __name__ == '__main__':
	start = datetime.date(2016,12,1)
	endtime = datetime.date(2017,1,1)
	r = search_word('减肥', starttime = start,endtime = endtime)
	