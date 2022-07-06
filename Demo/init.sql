insert into user values(20220628, "zhuyoucheng", "zhuyoucheng");
insert into user values(20220522, "huchengxing", "huchenxing");
insert into user values(20220501, "quhu", "quhu");
insert into user values(20220006, "zhangqingjun", "zhangqingjun");

insert into video values("0628_video", "food_ismn", "rnmCQNU", "food","food",true,"www.baidu.com", "2022-07-06", 20220628);
insert into video values("0522_video", "bbbbbbbbb", "bb","school","school",false, "www.xinlang.com", "2022-07-20", 20220522);
insert into video values("0001_video", "lovelove", "loveDiaraay", "love", "love", true, "www.aliyun.com", "2021-04-26", 20220006);

insert into videoFile values("0628_", "www.Youchengzhu.com", "0628_video");
insert into videoFile values("0522_", "www.YouchengZhu.com", "0522_video");

insert into fan values(20220628, "zhuyoucheng", 20220522, "huchenxing");
insert into fan values(20220628, "zhuyoucheng", 20220501, "quhu");
insert into fan values(20220522, "huchenxing", 20220501, "quhu");
insert into fan values(20220501, "quhu", 20220628, "zhuyoucheng");
insert into fan values(20220501, "quhu", 20220006, "zhangqingjun");

insert into follower values(20220628, "zhuyoucheng", 20220501, "quhu");
insert into follower values(20220522, "huchenxing", 20220628, "zhuyoucheng");
insert into follower values(20220501, "quhu", 202205022, "huchenxing");
insert into follower values(20220501, "quhu", 20220628, "zhuyoucheng");
insert into follower values(20220006, "zhangqingjun", 20220501, "quhu");


insert into comment values("0001", "这个视频真有意思啊", "0628_video", 20220522);
insert into comment values("0002", "啊啊啊啊，你干嘛", "0628_video", 20220501);
