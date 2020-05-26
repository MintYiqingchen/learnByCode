# coding:utf8
# usage of lxml

from lxml import etree

# PART1 CREATE A XML PAGE
root = etree.Element('root', id="test-id")

print(etree.iselement(root))

root.append( etree.Element("child1") )
child2 = etree.SubElement(root, "child2")
child3 = etree.SubElement(root, "child3")
print(etree.tostring(root,pretty_print=True))

# Element behaves like a list
root.insert(0,etree.Element('child0'))
print(etree.tostring(root))
root[-1]=root[0] # 只进行了引用拷贝！！变为只有三个孩子
print(etree.tostring(root))

assert(root is root[0].getparent()) # 获得父节点
assert(root[0] is root[1].getprevious())
assert(root[1] is root[0].getnext())

from copy import deepcopy

element =  etree.Element("newroot")
element.append( deepcopy(root[1]) ) #!!拷贝方法
element[0].tag = 'childxxx'
print([ x.tag for x in root ])

# ATTRIBUTES BEHAVE LIKE A DICT
root.set("class","room")
print(root.get("class"))

root.text="text"
print(etree.tostring(root))

# CREATE A REAL HTML
html = etree.Element('html')
body = etree.SubElement(html, 'body')
body.text = "Text"
br = etree.SubElement(body, 'br') # 只要里边没有内容，就不闭合
print(etree.tostring(html))
br.tail = "change line" # 要让里边加了内容也不闭合，tail text和text不一样
print(etree.tostring(html))
print(etree.tostring(br, with_tail=False))
print(etree.tostring(html, method="text"))

# USAGE OF XPATH
print("xpath for string: "+html.xpath("string()"))
print(html.xpath("//text()"))
build_text_list = etree.XPath("//text()") # a function
texts = build_text_list(html)
print(texts[0].getparent().tag, type(texts[0])) # 知道原来的位置

# TREE ITERATION
for element in html.iter():
	print(element.tag," ",element.text," ",element.tail)
	
# CREATE ElementTree
tree = etree.ElementTree(html)
assert(html is tree.getroot())

print( tree.xpath('//a') )

# find by ElementPath
root = etree.XML("<root><a x='123'>aText<b/><c/><b/></a></root>")
print(root.find("b")," ",root.find('a').tag) # only find a child
print(root.find('.//b').tag)
tree = etree.ElementTree(root)
a = root[0]
print(tree.getelementpath(a[0]))



