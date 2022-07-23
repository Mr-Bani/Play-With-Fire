//
// Created by Mahdi on 7/22/2022.
//

#include "Item.h"

Item::Item(int x, int y, int width, int height, int rand):positionX(x),positionY(y),width(width),height(height) {
    if(rand %4== 0){
        type = "infBomb";
        pixmap =  QPixmap(":/images/infBomb").scaled(width/2,height/2,Qt::IgnoreAspectRatio);
}
    else if(rand%5==0) {
        type = "heart";
        pixmap = (QPixmap(":/images/heart").scaled(width / 2, height / 2, Qt::IgnoreAspectRatio));

    }
    else if(rand%3==2){
        type = "speed";
        pixmap =  QPixmap(":/images/speed").scaled(width/2,height/2,Qt::IgnoreAspectRatio);
    }
    else{
        type="null";
        pixmap = QPixmap();
    }
    setPos(x+width/4,y+height/4);
    setPixmap(pixmap);
    qInfo()<<this<<" type:"<<type<<" "<<positionX<<" "<<positionY<<" "<<width<<" "<<height<<"\n";

    //QTimer::singleShot(5000,this,&Item::deleteItem);
}


QString Item::getType() {
    return type;
}
