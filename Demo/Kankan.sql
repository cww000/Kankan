create database if not exists Kankan default charset utf8mb4 collate utf8mb4_general_ci;


use Kankan;

create table user( 
	user_id BIGINT UNIQUE NOT NULL PRIMARY KEY, 
	user_key VARCHAR(20) NOT NULL, 
	user_nickname VARCHAR(10) UNIQUE
) DEFAULT CHARSET=utf8mb4 COMMENT="用户信息表";

create table video( 
	user_id BIGINT, 
	id VARCHAR(40) UNIQUE NOT NULL PRIMARY KEY,  
	description VARCHAR(60), 
	title VARCHAR(20) NOT NULL,  
	label VARCHAR(20), 
	subarea VARCHAR(20), 
	isOriginal boolean NOT NULL, 
	FOREIGN KEY(user_id) REFERENCES user(user_id)
) DEFAULT CHARSET=utf8mb4 COMMENT="稿件信息表";

create table fan( 
	user_id BIGINT, 
	user_nickname VARCHAR(10),
	fan_id BIGINT,
	fan_nickname VARCHAR(10)
) DEFAULT CHARSET=utf8mb4 COMMENT="粉丝表";

create table follower( 
	user_id BIGINT,
       	user_nickname VARCHAR(10),	
	follower_id BIGINT,
	follower_nickname VARCHAR(10)
) DEFAULT CHARSET=utf8mb4 COMMENT="关注者表";


