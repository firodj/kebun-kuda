# Brief

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

# Updates:

## Good: 1.0.3 tag

```
commit 52f90cda023abaca510d59f021c88629270ad6c0 (HEAD, tag: 1.0.3, refs/bisect/good-52f90cda023abaca510d59f021c88629270ad6c0)
Author: Nguyen Anh Quynh <aquynh@gmail.com>
Date:   Wed May 26 23:07:07 2021 +0800

    update ChangeLog
```

## Good: v1 branch

```
commit 63a445cbba18bf1313ac3699b5d25462b5d529f4 (HEAD)
Author: Dimitris Glynos <44968893+dglynos@users.noreply.github.com>
Date:   Mon Dec 13 02:40:32 2021 +0200

    fxsave / fxsave64 should store the floating point instruction pointer (fpip) (#1467)

    * fxsave / fxsave64 should store the floating point instruction pointer (fpip)
    - fxsave / fxsave64 happen to be used as GetPC code in exploits

    * unit tests for the storage of FPIP in fxsave (x86) and fxsave64 (x64)

```

## Issue Re-Appear:

```
commit aaaea14214ed46ac60cf7ef5766374f660b05777 (HEAD, refs/bisect/bad)
Author: Nguyen Anh Quynh <aquynh@gmail.com>
Date:   Sun Oct 3 22:14:44 2021 +0800

    import Unicorn2
```

### Unexpected:

```
0: read 2fff 8
0: read 2ff8 8
0: read 3000 8
3: write 2fff 8
3: write 2fff 1
3: write 3000 1
3: write 3001 1
3: write 3002 1
3: write 3003 1
3: write 3004 1
3: write 3005 1
3: write 3006 1
```

