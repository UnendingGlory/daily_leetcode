import matplotlib.pyplot as plt
# from matplotlib.ticker import mticker
# from matplotlib.font_manager import _rebuild

# _rebuild() #reload一下
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS'] #用来正常显示中文标签
plt.style.use('ggplot')
data = [12, 4.5, 1.4, 1.3, 1.3, 1.3, 1.25, 1.2, 1.2, 1.2]
labels = [u'明星', u'游戏', u'生活', u'学习', u'科技', u'音乐', u'时尚', u'电竞', u'电影', u'电视剧']

# plt.xlabel('示例x轴')
plt.ylabel('单位(千万)')
plt.grid(axis='x')
plt.bar(range(len(data)), data, tick_label=labels, color='orange')
plt.show()
