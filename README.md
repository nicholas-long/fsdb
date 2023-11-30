# fsdb project - file based database for partitioning and event sourced data

- concept of `file based database for partitioning and event sourced data`
  - like a local file storage version of a kafka database
- [20230930041146](https://github.com/nicholas-long/environment/blob/main/zet/20230930041146/README.md) fsdb developing ideas
- run build script `build-fsdb` to build optimized components.
  - i tried to make the whole thing with just scripts, but it is just too slow to handle billions of rows.
- fsdb can load roughly 30 million rows of real data per hour with a 12 core machine on a SSD
  - [20231004133128](https://github.com/nicholas-long/environment/blob/main/zet/20231004133128/README.md) an optimized hashcode generator for partitioning work into multiple processes

## how data is stored
- the first field of the data is regarded as an ID
- data stored as TSV or CSV in two partition files:
  - a compressed file holds all existing data
  - an uncompressed file holds recently added data.
    - this data can be compressed and appended to the compressed file periodically as data is inserted so the overall size of the database doesn't grow too fast
  - data is stored in partition files named after the partition number
- optionally store a timestamp with each row
  - [timestamps in fsdb](https://github.com/nicholas-long/environment/blob/main/zet/20231003063630/README.md)
  - should ignore it when printing unless provided with a command line option to print timestamp?
  - initialize database with `-t` to enable timestamps
  - search for timestamps using `searchtime` subcommand
- bloom filter could be optional feature implemented with hooks
  - [20231002021919](https://github.com/nicholas-long/environment/blob/main/zet/20231002021919/README.md) bloom filter for fsdb

## use cases
  - can use as large lookup table like dynamo db
- [20231003062001](https://github.com/nicholas-long/environment/blob/main/zet/20231003062001/README.md) fsdb use case - using as a set
- join with another file or stream piped to standard input. this is possible if the ID is the first column.

## implementation
- basic set of features / subcommands needed for database
  - initialize and set up number of partitions
  - search for one ID or multiple
  - search for IDs missing from the database - set difference
  - ingest data - pipe it into standard input and an awk script will put it where it belongs
  - print all data
  - compress subcommand - compress text files and append to gzip streams together. called by ingest when a partition gets too large

- testing timestamps for data
```bash
awk '
BEGIN {
  print systime()
}
'
1696194880
```

` zet/20230929145418/README.md `

# Related

- [20221008042814](https://github.com/nicholas-long/environment/blob/main/zet/20221008042814/README.md) WIP
- [20230928171946](https://github.com/nicholas-long/environment/blob/main/zet/20230928171946/README.md) data analysis scripting hub
- [20230929153207](https://github.com/nicholas-long/environment/blob/main/zet/20230929153207/README.md) computer science experiments hub
- [20230929194846](https://github.com/nicholas-long/environment/blob/main/zet/20230929194846/README.md) testing if shortcuts will work and not pick up extra files
- [20230930041146](https://github.com/nicholas-long/environment/blob/main/zet/20230930041146/README.md) fsdb developing ideas
- [20230930224454](https://github.com/nicholas-long/environment/blob/main/zet/20230930224454/README.md) problems encountered with zkvr while testing this environment
- [20231001151606](https://github.com/nicholas-long/environment/blob/main/zet/20231001151606/README.md) hashcodes for fsdb partitioning
- [20231001222624](https://github.com/nicholas-long/environment/blob/main/zet/20231001222624/README.md) test gzip append functionality
- [20221009192000](https://github.com/nicholas-long/environment/blob/main/zet/20221009192000/README.md) stuff to put on main page
- [20231003022851](https://github.com/nicholas-long/environment/blob/main/zet/20231003022851/README.md) data engineering hub
- [20231003062001](https://github.com/nicholas-long/environment/blob/main/zet/20231003062001/README.md) fsdb use cases
- [20231003063630](https://github.com/nicholas-long/environment/blob/main/zet/20231003063630/README.md) adding timestamps to fsdb
- [20231004133128](https://github.com/nicholas-long/environment/blob/main/zet/20231004133128/README.md) an optimized hashcode generator for partitioning work into multiple processes
- [20230905015223](https://github.com/nicholas-long/environment/blob/main/zet/20230905015223/README.md) install scripts
- [20231116151546](https://github.com/nicholas-long/environment/blob/main/zet/20231116151546/README.md) how to implement a modular subcommand with lightweight scripts - ideas for a blog post
- [20231122053807](https://github.com/nicholas-long/environment/blob/main/zet/20231122053807/README.md) fsdb implementation details
- [20231122231545](https://github.com/nicholas-long/environment/blob/main/zet/20231122231545/README.md) publishing fsdb to github as a standalone project in a repository

Tags:

    #data #file #database #project #shortcmd
