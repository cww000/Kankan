insert into user values(20220628, "zhuyoucheng", "朱有成");
insert into user values(20220522, "huchengxing", "胡琛星");
insert into user values(20220501, "quhu", "屈虎");
insert into user values(20220006, "zhangqingjun", "张青军");

insert into video values(20220628, "0628_video", "第一个稿件", "rnmCQNU", "美食","美食",true);
insert into video values(20220522, "0522_video", "今天是星期二，他们毕业了", "毕业季","校园","校园",false);
insert into video values(20220006, "0001_video", "恋爱啊", "恋爱日记", "恋爱", "恋爱", true);

insert into fan values(20220628, "朱有成", 20220522, "胡琛星");
insert into fan values(20220628, "朱有成", 20220501, "屈虎");
insert into fan values(20220522, "胡琛星", 20220501, "屈虎");
insert into fan values(20220501, "屈虎", 20220628, "朱有成");
insert into fan values(20220501, "屈虎", 20220006, "张青军");

insert into follower values(20220628, "朱有成", 20220501, "屈虎");
insert into follower values(20220522, "胡琛星", 20220628, "朱有成");
insert into follower values(20220501, "屈虎", 202205022, "胡琛星");
insert into follower values(20220501, "屈虎", 20220628, "朱有成");
insert into follower values(20220006, "张青军", 20220501, "屈虎");
