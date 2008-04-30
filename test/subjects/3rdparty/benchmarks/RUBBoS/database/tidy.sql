DELETE FROM `comments` WHERE `date` > '2008-1-1';
DELETE FROM `moderator_log` WHERE `date` > '2008-1-1';
DELETE FROM `stories` WHERE `date` > '2008-1-1';
DELETE FROM `submissions` WHERE `date` > '2008-1-1';
DELETE FROM `users` WHERE `creation_date` > '2008-1-1';
OPTIMIZE TABLE comments, moderator_log, stories, submissions, users;
