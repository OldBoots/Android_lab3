#include "mainwindow.h"
#include "ui_mainwindow.h"

//PUBLIC
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

    ui->ico_u->setPixmap(QPixmap(":/uan.png").scaled(16, 16, Qt::KeepAspectRatio));
    ui->ico_t->setPixmap(QPixmap(":/clocks.png").scaled(16, 16, Qt::KeepAspectRatio));

    scene = new QGraphicsScene(ui->graphicsView);
    scene->setSceneRect(0, 0, sw, sh);
    game_over = new QGraphicsTextItem;

    rect_end = new QGraphicsRectItem;
    rect_end->setRect(0, sh - 16, sw, 16);
    rect_end->setPen(QPen(Qt::red));
    scene->addItem(rect_end);

    scene->setBackgroundBrush(QBrush(QPixmap(":/BackGround.png").scaled(sw, sh)));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    time = 0;
    uan = 0;

    timer_game = new QTimer;
    timer_bug = new QTimer;
    connect(timer_game, SIGNAL(timeout()), this, SLOT(slot_each_sec()));
    connect(timer_bug, SIGNAL(timeout()), this, SLOT(slot_chec_stop()));
    connect(ui->butt_start, SIGNAL(clicked()), this, SLOT(slot_start_game()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//PRIVATE SLOTS
void MainWindow::slot_each_sec(){
    time++;
    ui->lbl_count_t->setText(QString::number(time));
    for(int i = 0; i < vec_bugs.size(); i++){       // Убераем трупы - получаем деньги
        if(!vec_bugs[i]->get_cur_state()){
            uan += vec_bugs[i]->get_reward();
            ui->lbl_count_u->setText(QString::number(uan));
            scene->removeItem(vec_bugs[i]);
            vec_bugs.remove(i);
        }
    }
    int n_bug, x;                                   // Спавним новых гадов
    n_bug = Rand(0, 3);
    for(int i = 0; i < n_bug; i++){
        x = Rand(0, sw - 64);
        vec_bugs << new Bug(Rand(0, 1));
        scene->addItem(vec_bugs[vec_bugs.size() - 1]);
        vec_bugs[vec_bugs.size() - 1]->setPos(x, 0);
        connect(timer_bug, SIGNAL(timeout()), vec_bugs[vec_bugs.size() - 1], SLOT(slot_timer_ev()));
    }
}

void MainWindow::slot_start_game(){
    scene->removeItem(game_over);   // Чистим
    time = 0;
    uan = 0;
    ui->lbl_count_t->setText("0");
    ui->lbl_count_u->setText("0");
    for(int i = vec_bugs.size() - 1; i >= 0; i--){
        scene->removeItem(vec_bugs[i]);
        vec_bugs.pop_back();
    }
    timer_bug->stop();             // Перезапускаем
    timer_bug->start(250);
    timer_game->stop();
    timer_game->start(1000);
}

void MainWindow::slot_chec_stop(){
    if(!scene->collidingItems(rect_end).isEmpty()){
        timer_bug->stop();
        timer_game->stop();
        for(int i = vec_bugs.size() - 1; i >= 0 ; i--){
            scene->removeItem(vec_bugs[i]);
            vec_bugs.pop_back();
        }
        game_over->setPlainText("ИГРА ОКОНЧЕНА\nЮани: " + ui->lbl_count_u->text() + "\nВремя: " + ui->lbl_count_t->text());
        game_over->setFont(QFont("AppleSystemUIFont", 28));
        scene->addItem(game_over);
        game_over->setPos(sw / 2 - 115, sh / 2 - 64);
        game_over->setDefaultTextColor(Qt::red);
    }

}

//OTHER
int Rand(int min, int max){
    if (min == max){
        return min;
    }
    std::uniform_int_distribution dist(min, max);
    return dist(*QRandomGenerator::global());
}



