#include <iostream>
#include "json.hpp"
#include "videosocialcontrol.h"
#include "json.hpp"
using namespace std;

int main()
{
    VideoSocialControl control;
    //登陆
    std::cout << "========================================\n";
    std::cout << "显示已登陆网民信息：\n";
    control.login("20220628", "zhuyoucheng");
//    control.login("20220522", "huchengxing");
//    control.login("20220501", "quhu");
//    control.login("20220006", "zhangqingjun");

    std::cout << "========================================\n";
    //网民查看某个视频
    std::cout << "网民 quhu 选择查看某个视频：\n";
    control.checkOneVideo("20220501", "0628_video");

    //删除网民的某个视频
  //  control.deleteVideo("20220628", "0628_video");

    //发布视频
    nlohmann::json video;
    video["description"] = "food_ismn";
    video["title"] = "rnmCQNU";
    video["label"] = "food";
    video["subarea"] = "food";
    video["isOriginal"] = "true";
    video["cover"] = "www.baidu.com";
    video["date"] = "2022-07-06";
    video["user_id"] = "20220628";
    video["videoFile"]["id"] = "0628_";
 //   control.createVideo("20220628", video);

    //上线的粉丝浏览离线缓存消息
    control.browseMessage("20220501");

    //粉丝查看某个离线缓存的消息
    control.checkOneMessage("20220501", "2");

    //某个网民修改自己的个人信息
    control.updateAcountInfo("20220522", "huchengxing", "www.com","huchenxing");

    //某个网民修改自己的已发布的某个视频的信息
    nlohmann::json newVideo;
    newVideo["id"] = "0628_video";
    newVideo["description"] = "food_ismn";
    newVideo["title"] = "CQNU";
    newVideo["label"] = "food";
    newVideo["subarea"] = "food";
    newVideo["isOriginal"] = "true";
    newVideo["cover"] = "www.taobao.com";
    newVideo["date"] = "2022-07-22";
    newVideo["user_id"] = "20220628";
    newVideo["videoFile"]["id"] = "0628_";
    control.updateVideoInfo("20220628", newVideo);


    //关注
  //  control.follow("20220006", "20220628");

    //评论
  //  control.commentVideo("这个视频可真有意思！！", "20220006", "0628_video");

    return 0;
}
