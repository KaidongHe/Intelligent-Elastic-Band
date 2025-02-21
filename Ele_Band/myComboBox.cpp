/**
*****************************************************************************
*  Copyright (C), 仅供实验室内部使用，未经许可请勿外传
*
*  @file    myComboBox.cpp
*  @brief   自定义ComboBox类
*           1.实现按下串口ComboBox自动搜索串口
*
*  @author  kdh
*  @date    2024-05-20
*  @version V1.1.1 2024-05-20
*  @advice  尽量不要将各个功能都在同一文件中实现
*           文件解耦会极大提高工程可扩展性、可测试性,保证软件效率和质量
*----------------------------------------------------------------------------
*  @note 历史版本     修改人员        修改日期        修改内容
*  @note v1.0.0      kdh           2023-12-20     创建
*  @note v1.1.0      kdh           2024-05-08     完成基本功能
*****************************************************************************
**/
#include "myComboBox.h"

MyComboBox::MyComboBox(QWidget *parent):QComboBox(parent)
{

}

MyComboBox::~MyComboBox()
{

}

void MyComboBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit clicked();     //触发clicked信号
    }

    //将该事件传给父类处理，这句话很重要，如果没有，父类无法处理本来的点击事件
    QComboBox::mousePressEvent(event);
}
