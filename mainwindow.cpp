#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->screen()->size());
    ss = this->size();
    sh = ss.height() - 206;
    sw = ss.width() - 15;
    qDebug() << "sw= " << sw << " sh = " << sh;

    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, sw, sh);
    game_over = new QGraphicsTextItem;

    rect_end = new QGraphicsRectItem;
    rect_end->setRect(0, sh - 16, sw, 16);
    rect_end->setPen(QPen(Qt::red));
    scene->addItem(rect_end);

//    border = new QGraphicsLineItem[4];
//    border[0].setLine(0, 0, sw, 0);
//    border[1].setLine(sw, 0, sw, sh);
//    border[2].setLine(sw, sh, 0, sh);
//    border[3].setLine(0, sh, 0, 0);
//    scene->addItem(&border[0]);
//    scene->addItem(&border[1]);
//    scene->addItem(&border[2]);
//    scene->addItem(&border[3]);
    scene->setBackgroundBrush(QBrush(QPixmap(":/BackGround.png").scaled(sw, sh)));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    time = 0;

    timer_game = new QTimer;
    timer_bug = new QTimer;
    connect(timer_game, SIGNAL(timeout()), this, SLOT(slot_charge_timer()));
    connect(timer_bug, SIGNAL(timeout()), this, SLOT(slot_chec_stop()));
    connect(ui->butt_start, SIGNAL(clicked()), this, SLOT(slot_start_game()));
}

void MainWindow::slot_spawn_bug(){
    vec_bugs << new Bug(1);
    scene->addItem(vec_bugs[vec_bugs.size() - 1]);
    vec_bugs[vec_bugs.size() - 1]->setPos(0, 0);
    connect(timer_bug, SIGNAL(timeout()), vec_bugs[vec_bugs.size() - 1], SLOT(slot_timer_ev()));
}

void MainWindow::slot_charge_timer(){
    time++;
    ui->lbl_count_time->setText(QString::number(time));
}

void MainWindow::slot_start_game(){
    scene->removeItem(game_over);
    time = 0;
    ui->lbl_count_time->setText("0");
    slot_spawn_bug();
    timer_bug->stop();
    timer_bug->start(250);
    timer_game->stop();
    timer_game->start(1000);
}

void MainWindow::slot_chec_stop(){
    if(!scene->collidingItems(vec_bugs[0]).isEmpty()){
        qDebug("AAAAAAA");
        stop_game();
    }
//    for(int i = 0; i < vec_bugs.size(); i++){
//        if(rect_end->collidesWithItem(vec_bugs[i], Qt::IntersectsItemBoundingRect)){
//            qDebug("AAAAAAA");
//
//        }
//    }
}

void MainWindow::stop_game(){
    timer_bug->stop();
    timer_game->stop();
    for(int i = vec_bugs.size() - 1; i >= 0 ; i--){
        scene->removeItem(vec_bugs[i]);
        vec_bugs.pop_back();
    }
    game_over->setPlainText("ИГРА ОКОНЧЕНА\n" + ui->lbl_count_bug->text() + " " + ui->lbl_count_time->text());
    game_over->setFont(QFont("AppleSystemUIFont", 28));
    scene->addItem(game_over);
    game_over->setPos(sw / 2 - 115, sh / 2 - 64);
    game_over->setDefaultTextColor(Qt::red);

    ui->lbl_count_bug->setText("0");
    ui->lbl_count_time->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

