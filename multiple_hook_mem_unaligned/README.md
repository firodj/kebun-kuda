Issue: https://github.com/unicorn-engine/unicorn/issues/1041

Fixed On:

```
commit 6cad700b69678c1dea3a174514640fded0496e59 (HEAD)
Author: BrunoPujos <28804193+BrunoPujos@users.noreply.github.com>
Date:   Mon May 25 10:22:28 2020 +0200

    fix recursive UC_HOOK_MEM callbacks for cross pages access (#1113)

    Co-authored-by: bruno <bruno>
    Co-authored-by: Nguyen Anh Quynh <aquynh@gmail.com>
```

Expected Output:
```
0: read 2fff 8
3: write 2fff 8
```

Updates:

Good:

```
commit 52f90cda023abaca510d59f021c88629270ad6c0 (HEAD, tag: 1.0.3, refs/bisect/good-52f90cda023abaca510d59f021c88629270ad6c0)
Author: Nguyen Anh Quynh <aquynh@gmail.com>
Date:   Wed May 26 23:07:07 2021 +0800

    update ChangeLog
```