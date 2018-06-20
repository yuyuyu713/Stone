
import tushare as ts

# # d = ts.get_tick_data('601318',date='2017-06-26')
# # print(d)
# e = ts.get_hist_data('000858',start='2017-04-01',end='2017-04-15')
# print(e)


# stock_info = ts.get_stock_basics()

# codelist = ['002225','600313','002909']
# codelist = stock_info.index
#获取所有股票代码
# for code in stock_info.index:
#     print('正在获取股票%s数据' % code)
#     df_hist_data = ts.get_hist_data(code, end='2018-06-19')
#     df_hist_data.to_csv (filepath+str(code)+".csv" , encoding = "utf-8")

# print(ts.get_industry_classified())

stockClassList = ['行业分类','概念分类','地域分类','中小板分类','创业板分类','风险警示板分类','沪深300成份及权重','上证50成份股','中证500成份股','终止上市股票列表','暂停上市股票列表']

def saveCsv(data, path, list, index):
    data.to_csv(path+list[index]+str(".csv"), encoding="utf-8")

def getStockClassfied():
    filepath = 'f:\\stockdata\\股票分类数据\\'
    index = 0
    # 行业分类
    df = ts.get_industry_classified()
    saveCsv(df, filepath, stockClassList, index)
    index += 1

    # 概念分类
    df = ts.get_concept_classified()
    saveCsv(df, filepath, stockClassList, index)
    index += 1

    # 地域分类
    df = ts.get_area_classified()
    saveCsv(df, filepath, stockClassList, index)
    index += 1
    # 中小板分类
    df = ts.get_sme_classified()
    saveCsv(df, filepath, stockClassList, index)
    index += 1
    # 创业板分类
    df = ts.get_gem_classified()
    saveCsv(df, filepath, stockClassList, index)
    index += 1
    # 风险警示板分类
    df = ts.get_st_classified()
    saveCsv(df, filepath, stockClassList, index)
    index += 1
    # 沪深300成份及权重
    df = ts.get_hs300s()
    saveCsv(df, filepath, stockClassList, index)
    index += 1
    # 上证50成份股
    df = ts.get_sz50s()
    saveCsv(df, filepath, stockClassList, index)
    index += 1
    # 中证500成份股
    df = ts.get_zz500s()
    saveCsv(df, filepath, stockClassList, index)
    index += 1

    # 接口暂时不能使用
    # # 终止上市股票列表 HTTP Error 403: Forbidden / None
    # df = ts.get_terminated()
    # saveCsv(df, filepath, stockClassList, index)
    # index += 1
    # # 暂停上市股票列表 HTTP Error 403: Forbidden / None
    # df = ts.get_suspended()
    # saveCsv(df, filepath, stockClassList, index)
    # index += 1



# 基本面数据

panelList = [
'沪深股票列表',
# '业绩预告',
'业绩报告（主表）-2014-03',
'盈利能力数据-2014-03',
'营运能力数据-2014-03',
'成长能力数据-2014-03',
'偿债能力数据-2014-03',
'现金流量数据-2014-03']

def getPanelData():
    filepath = 'f:\\stockdata\\基本面数据\\'
    index = 0

    # 沪深股票列表
    # code, 代码
    # name, 名称
    # industry, 所属行业
    # area, 地区
    # pe, 市盈率
    # outstanding, 流通股本(亿)
    # totals, 总股本(亿)
    # totalAssets, 总资产(万)
    # liquidAssets, 流动资产
    # fixedAssets, 固定资产
    # reserved, 公积金
    # reservedPerShare, 每股公积金
    # esp, 每股收益
    # bvps, 每股净资
    # pb, 市净率
    # timeToMarket, 上市日期
    # undp, 未分利润
    # perundp, 每股未分配
    # rev, 收入同比( %)
    # profit, 利润同比( %)
    # gpr, 毛利率( %)
    # npr, 净利润率( %)
    # holders, 股东人数
    df = ts.get_stock_basics()
    saveCsv(df, filepath, panelList, index)
    index += 1

    # 业绩预告？？

    # 业绩报告（主表）
    # code, 代码
    # name, 名称
    # esp, 每股收益
    # eps_yoy, 每股收益同比( %)
    # bvps, 每股净资产
    # roe, 净资产收益率( %)
    # epcf, 每股现金流量(元)
    # net_profits, 净利润(万元)
    # profits_yoy, 净利润同比( %)
    # distrib, 分配方案
    # report_date, 发布日期
    # 获取2014年第3季度的业绩报表数据
    df = ts.get_report_data(2014, 3)
    saveCsv(df, filepath, panelList, index)
    index += 1

    # 盈利能力数据
    # code, 代码
    # name, 名称
    # roe, 净资产收益率( %)
    # net_profit_ratio, 净利率( %)
    # gross_profit_rate, 毛利率( %)
    # net_profits, 净利润(万元)
    # esp, 每股收益
    # business_income, 营业收入(百万元)
    # bips, 每股主营业务收入(元)
    # 获取2014年第3季度的盈利能力数据
    df = ts.get_profit_data(2014, 3)
    saveCsv(df, filepath, panelList, index)
    index += 1

    # 营运能力数据
    # code, 代码
    # name, 名称
    # arturnover, 应收账款周转率(次)
    # arturndays, 应收账款周转天数(天)
    # inventory_turnover, 存货周转率(次)
    # inventory_days, 存货周转天数(天)
    # currentasset_turnover, 流动资产周转率(次)
    # currentasset_days, 流动资产周转天数(天)
    # 获取2014年第3季度的营运能力数据
    df = ts.get_operation_data(2014, 3)
    saveCsv(df, filepath, panelList, index)
    index += 1

    # 成长能力数据
    # code, 代码
    # name, 名称
    # mbrg, 主营业务收入增长率( %)
    # nprg, 净利润增长率( %)
    # nav, 净资产增长率
    # targ, 总资产增长率
    # epsg, 每股收益增长率
    # seg, 股东权益增长率
    # 获取2014年第3季度的成长能力数据
    df = ts.get_growth_data(2014, 3)
    saveCsv(df, filepath, panelList, index)
    index += 1

    # 偿债能力数据
    # code, 代码
    # name, 名称
    # currentratio, 流动比率
    # quickratio, 速动比率
    # cashratio, 现金比率
    # icratio, 利息支付倍数
    # sheqratio, 股东权益比率
    # adratio, 股东权益增长率
    # 获取2014年第3季度的偿债能力数据
    df = ts.get_debtpaying_data(2014, 3)
    saveCsv(df, filepath, panelList, index)
    index += 1

    # 现金流量数据
    # code, 代码
    # name, 名称
    # cf_sales, 经营现金净流量对销售收入比率
    # rateofreturn, 资产的经营现金流量回报率
    # cf_nm, 经营现金净流量与净利润的比率
    # cf_liabilities, 经营现金净流量对负债比率
    # cashflowratio, 现金流量比率
    #获取2014年第3季度的现金流量数据
    df = ts.get_cashflow_data(2014,3)
    saveCsv(df, filepath, panelList, index)
    index += 1


## 投资参考数据
investList = [
'分配预案',
'业绩预告',
'限售股解禁',
'基金持股',
'新股上市',
'沪市融资融券汇总数据',
'沪市融资融券明细数据',
'深市融资融券汇总数据',
'深市融资融券明细数据']

def getInvestData():
    filepath = 'f:\\stockdata\\投资参考数据\\'
    index = 0

    # 分配预案
    #     参数说明：
    #     year: 预案公布的年份，默认为2014
    #     top: 取最新n条数据，默认取最近公布的25条
    #     retry_count：当网络异常后重试次数，默认为3
    #     pause: 重试时停顿秒数，默认为0
    #     返回值说明：
    #     code: 股票代码
    #     name: 股票名称
    #     year: 分配年份
    #     report_date: 公布日期
    #     divi: 分红金额（每10股）
    #     shares: 转增和送股数（每10股）
    df = ts.profit_data(top=60)
    # df.sort('shares', ascending=False)
    saveCsv(df, filepath, investList, index)
    index += 1


    # 业绩预告
    #     参数说明：
    #       year: int 年度 e.g: 2014
    #       quarter: int 季度: 1、2、3、4，只能输入这4个季度
    #     返回值说明：
    #       code, 代码
    #       name, 名称
    #       type, 业绩变动类型【预增、预亏等】
    #       report_date, 发布日期
    #       pre_eps, 上年同期每股收益
    #       range, 业绩变动范围
    # 获取2014年中报的业绩预告数据
    df = ts.forecast_data(2014, 2)
    saveCsv(df, filepath, investList, index)
    index += 1

    # 限售股解禁
    #     参数说明：
    #     year: 年份, 默认为当前年
    #     month: 解禁月份，默认为当前月
    #     retry_count：当网络异常后重试次数，默认为3
    #     pause: 重试时停顿秒数，默认为0
    #     返回值说明：
    #     code：股票代码
    #     name：股票名称
    #     date: 解禁日期
    #     count: 解禁数量（万股）
    #     ratio: 占总盘比率
    df = ts.xsg_data()
    saveCsv(df, filepath, investList, index)
    index += 1


    # 基金持股
        # 参数说明：
        # year: 年份, 默认为当前年
        # quarter: 季度（只能输入1，2，3，4
        # 这个四个数字）
        # retry_count：当网络异常后重试次数，默认为3
        # pause: 重试时停顿秒数，默认为0
        # 返回值说明：
        # code：股票代码
        # name：股票名称
        # date: 报告日期
        # nums: 基金家数
        # nlast: 与上期相比（增加或减少了）
        # count: 基金持股数（万股）
        # clast: 与上期相比
        # amount: 基金持股市值
        # ratio: 占流通盘比率
    df = ts.fund_holdings(2014, 4)
    saveCsv(df, filepath, investList, index)
    index += 1


    # 新股上市
    #     参数说明：
    #     retry_count：当网络异常后重试次数，默认为3
    #     pause: 重试时停顿秒数，默认为0
    #     返回值说明：
    #     code：股票代码
    #     name：股票名称
    #     ipo_date: 上网发行日期
    #     issue_date: 上市日期
    #     amount: 发行数量(万股)
    #     markets: 上网发行数量(万股)
    #     price: 发行价格(元)
    #     pe: 发行市盈率
    #     limit: 个人申购上限(万股)
    #     funds：募集资金(亿元)
    #     ballot: 网上中签率( %)
    df = ts.new_stocks()
    saveCsv(df, filepath, investList, index)
    index += 1


    # 沪市融资融券汇总数据
    #     参数说明：
    #     start: 开始日期
    #     format：YYYY - MM - DD
    #     为空时取去年今日
    #     end: 结束日期
    #     format：YYYY - MM - DD
    #     为空时取当前日期
    #     retry_count：当网络异常后重试次数，默认为3
    #     pause: 重试时停顿秒数，默认为0
    #     返回值说明：
    #     opDate: 信用交易日期
    #     rzye: 本日融资余额(元)
    #     rzmre: 本日融资买入额(元)
    #     rqyl: 本日融券余量
    #     rqylje: 本日融券余量金额(元)
    #     rqmcl: 本日融券卖出量
    #     rzrqjyzl: 本日融资融券余额(元)
    # df = ts.sh_margins(start='2015-01-01', end='2015-04-19')
    # saveCsv(df, filepath, investList, index)
    index += 1

    # 沪市融资融券明细数据
    #     参数说明：
    #     date: 日期
    #     format：YYYY - MM - DD
    #     默认为空’‘, 数据返回最近交易日明细数据
    #     symbol：标的代码，6
    #     位数字e.g
    #     .600848，默认为空’‘
    #     start: 开始日期
    #     format：YYYY - MM - DD
    #     默认为空’‘
    #     end: 结束日期
    #     format：YYYY - MM - DD
    #     默认为空’‘
    #     retry_count：当网络异常后重试次数，默认为3
    #     pause: 重试时停顿秒数，默认为0
    #     返回值说明：
    #     opDate: 信用交易日期
    #     stockCode: 标的证券代码
    #     securityAbbr: 标的证券简称
    #     rzye: 本日融资余额(元)
    #     rzmre: 本日融资买入额(元)
    #     rzche: 本日融资偿还额(元)
    #     rqyl: 本日融券余量
    #     rqmcl: 本日融券卖出量
    #     rqchl: 本日融券偿还量
    # df = ts.sh_margin_details(start='2015-01-01', end='2015-04-19', symbol='601989')
    # #如果不设symbol参数或者开始和结束日期时段设置过长，数据获取可能会比较慢，建议分段分步获取，比如一年为一个周期
    # saveCsv(df, filepath, investList, index)
    index += 1


    # 深市融资融券汇总数据
    #     参数说明：
    #     start: 开始日期
    #     format：YYYY - MM - DD
    #     为空时取去年今日
    #     end: 结束日期
    #     format：YYYY - MM - DD
    #     为空时取当前日期
    #     retry_count：当网络异常后重试次数，默认为3
    #     pause: 重试时停顿秒数，默认为0
    #     返回值说明：
    #     opDate: 信用交易日期(index)
    #     rzmre: 融资买入额(元)
    #     rzye: 融资余额(元)
    #     rqmcl: 融券卖出量
    #     rqyl: 融券余量
    #     rqye: 融券余量(元)
    #     rzrqye: 融资融券余额(元)
    # df = ts.sz_margins(start='2015-01-01', end='2015-04-19')
    # saveCsv(df, filepath, investList, index)
    index += 1

    # 沪市融资融券明细数据
    #     参数说明：
    #     date:日期 format：YYYY-MM-DD 默认为空’‘,数据返回最近交易日明细数据
    #     symbol：标的代码，6位数字e.g.600848，默认为空’‘
    #     start:开始日期 format：YYYY-MM-DD 默认为空’‘
    #     end:结束日期 format：YYYY-MM-DD 默认为空’‘
    #     retry_count：当网络异常后重试次数，默认为3
    #     pause:重试时停顿秒数，默认为0
    #     返回值说明：
    #     opDate:信用交易日期
    #     stockCode:标的证券代码
    #     securityAbbr:标的证券简称
    #     rzye:本日融资余额(元)
    #     rzmre: 本日融资买入额(元)
    #     rzche:本日融资偿还额(元)
    #     rqyl: 本日融券余量
    #     rqmcl: 本日融券卖出量
    #     rqchl: 本日融券偿还量
    # df = ts.sh_margin_details(start='2015-01-01', end='2015-04-19', symbol='601989')
    # #如果不设symbol参数或者开始和结束日期时段设置过长，数据获取可能会比较慢，建议分段分步获取，比如一年为一个周期
    # saveCsv(df, filepath, investList, index)
    index += 1

# getStockClassfied()
# getPanelData()

#投资参考数据
getInvestData()