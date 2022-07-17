create database if not exists Kankan default charset utf8mb4 collate utf8mb4_general_ci;


use Kankan;

create table user( 
	user_id BIGINT UNIQUE NOT NULL PRIMARY KEY, 
	user_key VARCHAR(20) NOT NULL, 
	user_nickname VARCHAR(20) UNIQUE
) DEFAULT CHARSET=utf8mb4 COMMENT="用户信息表";

create table video( 
	id VARCHAR(30) UNIQUE NOT NULL PRIMARY KEY,  
	description VARCHAR(30), 
	title VARCHAR(30) NOT NULL,  
	label VARCHAR(20), 
	subarea VARCHAR(20), 
	isOriginal boolean NOT NULL, 
	cover VARCHAR(30) NOT NULL,
	date VARCHAR(30) NOT NULL,
	user_id BIGINT,
	FOREIGN KEY(user_id) REFERENCES user(user_id)
) DEFAULT CHARSET=utf8mb4 COMMENT="稿件信息表";

create table videoFile(
	id VARCHAR(30) UNIQUE NOT NULL PRIMARY KEY,
	address VARCHAR(30) NOT NULL,
	videoId VARCHAR(30),
	FOREIGN KEY(videoId) REFERENCES video(id) on delete cascade
) DEFAULT CHARSET=utf8mb4 COMMENT="视频文件数据表";

create table fan( 
	user_id BIGINT NOT NULL, 
	user_nickname VARCHAR(20),
	fan_id BIGINT NOT NULL,
	fan_nickname VARCHAR(20),
	PRIMARY KEY (user_id, fan_id)
) DEFAULT CHARSET=utf8mb4 COMMENT="粉丝表";

create table follower( 
	user_id BIGINT NOT NULL,
	user_nickname VARCHAR(20),	
	follower_id BIGINT NOT NULL,
	follower_nickname VARCHAR(20),
	PRIMARY KEY (user_id, follower_id)
) DEFAULT CHARSET=utf8mb4 COMMENT="关注者表";

create table comment(
	id VARCHAR(30) UNIQUE NOT NULL PRIMARY KEY,
	text VARCHAR(30) NOT NULL,
	videoId VARCHAR(30) NOT NULL,
	user_id BIGINT
) DEFAULT CHARSET=utf8mb4 COMMENT="评论表";

create table message(
	id VARCHAR(30) UNIQUE NOT NULL PRIMARY KEY,
	content VARCHAR(200),
	date VARCHAR(30),
	senderId BIGINT UNIQUE NOT NULL,
	videoId	VARCHAR(30)
) DEFAULT CHARSET=utf8mb4 COMMENT="消息表";

create table send(
	messageId VARCHAR(3) NOT NULL,
	fanId BIGINT NOT NULL,
	FOREIGN KEY(messageId) REFERENCES message(id) on delete cascade
) DEFAULT CHARSET=utf8mb4 COMMENT="接收表";
	
	
