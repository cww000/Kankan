#include <iostream>
#include "videosocialcontrol.h"

using namespace std;

int main()
{
    VideoSocialControl control;
    //登陆
    control.login(20220628, "zhuyoucheng");
    control.login(20220522, "huchengxing");
    control.login(20220501, "quhu");
    control.login(20220006, "zhangqingjun");

    //删除网民的某个稿件
 //   control.deleteVideo(20220628, "0628_video");

    //发布稿件
    control.createVideo("food_ismn", "rnmCQNU", "food","food",true,"www.baidu.com", "2022-07-06", 20220628, "0628_");

    //在线的粉丝查看离线缓存的消息
    control.checkOneMessage(20220522, "2");

    //某个网民修改自己的个人信息
    control.updateAcountInfo(20220522, "huchengxing", "www.com","huchenxing");

    //关注
    control.follow(20220006, 20220628);

    //评论
    control.commentVideo("这个视频可真有意思！！", 20220006, "0628_video");


    //  control.login(1657854523, "chengwenwen");
    //control.login("lwc");

    return 0;
}
