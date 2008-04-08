CREATE DATABASE rubbos;
connect rubbos;

CREATE TABLE categories (
   id INTEGER UNSIGNED NOT NULL UNIQUE,
   name VARCHAR(50),
   PRIMARY KEY(id)
);

CREATE TABLE users (
   id            INTEGER UNSIGNED UNIQUE AUTO_INCREMENT,
   firstname     VARCHAR(20),
   lastname      VARCHAR(20),
   nickname      VARCHAR(20) NOT NULL UNIQUE,
   password      VARCHAR(20) NOT NULL,
   email         VARCHAR(50) NOT NULL,
   rating        INTEGER,
   access        INTEGER,
   creation_date DATETIME,
   PRIMARY KEY(id),
   INDEX auth (nickname,password),
   INDEX search (nickname)
);

INSERT INTO users VALUES (0, "Anonymous", "Coward", "Anonymous Coward", "+_)(*&^%$#@!", "anonymous@rubbos.com", 0, 0, NOW());
UPDATE users SET id=0 WHERE nickname="Anonymous Coward";

CREATE TABLE stories (
   id            INTEGER UNSIGNED NOT NULL UNIQUE AUTO_INCREMENT,
   title         VARCHAR(100),
   body          TEXT,
   date          DATETIME,
   writer        INTEGER UNSIGNED NOT NULL,
   category      INTEGER UNSIGNED NOT NULL,
   PRIMARY KEY(id),
   INDEX writer_id (writer),
   INDEX category_id (category),
   INDEX search (title(10)),
   INDEX day (date)
);

CREATE TABLE old_stories (
   id            INTEGER UNSIGNED NOT NULL UNIQUE AUTO_INCREMENT,
   title         VARCHAR(100),
   body          TEXT,
   date          DATETIME,
   writer        INTEGER UNSIGNED NOT NULL,
   category      INTEGER UNSIGNED NOT NULL,
   PRIMARY KEY(id),
   INDEX writer_id (writer),
   INDEX category_id (category),
   INDEX search (title(10)),
   INDEX day (date)
);

CREATE TABLE submissions (
   id            INTEGER UNSIGNED NOT NULL UNIQUE AUTO_INCREMENT,
   title         VARCHAR(100),
   body          TEXT,
   date          DATETIME,
   writer        INTEGER UNSIGNED,
   category      INTEGER UNSIGNED NOT NULL,
   PRIMARY KEY(id),
   INDEX writer_id (writer),
   INDEX category_id (category),
   INDEX day (date)
);

CREATE TABLE comments (
   id           INTEGER UNSIGNED NOT NULL UNIQUE AUTO_INCREMENT,
   writer       INTEGER UNSIGNED,
   story_id     INTEGER UNSIGNED NOT NULL,
   parent       INTEGER UNSIGNED,
   childs       INTEGER UNSIGNED,
   rating       INTEGER,
   date         DATETIME,
   subject      VARCHAR(100),
   comment      TEXT,
   PRIMARY KEY(id),
   INDEX story (story_id),
   INDEX search (subject(10)),
   INDEX parent_id (parent),
   INDEX rating_num (rating)
);


CREATE TABLE old_comments (
   id           INTEGER UNSIGNED NOT NULL UNIQUE AUTO_INCREMENT,
   writer       INTEGER UNSIGNED,
   story_id     INTEGER UNSIGNED NOT NULL,
   parent       INTEGER UNSIGNED,
   childs       INTEGER UNSIGNED,
   rating       INTEGER,
   date         DATETIME,
   subject      VARCHAR(100),
   comment      TEXT,
   PRIMARY KEY(id),
   INDEX story (story_id),
   INDEX search (subject(10)),
   INDEX parent_id (parent),
   INDEX rating_num (rating)
);

CREATE TABLE moderator_log (
   id           INTEGER UNSIGNED NOT NULL UNIQUE AUTO_INCREMENT,
   moderator_id INTEGER UNSIGNED NOT NULL,
   comment_id   INTEGER UNSIGNED NOT NULL,
   rating       INTEGER,
   date         DATETIME,
   PRIMARY KEY(id),
   INDEX comment (comment_id)
);
