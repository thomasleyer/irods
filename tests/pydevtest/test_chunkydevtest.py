import os, stat
        
        # new file mode check
        assertiCmd(s.adminsession,"iget -fK --rlock "+irodshome+"/icmdtest/foo2 /tmp/" )
        assert oct(stat.S_IMODE(os.stat("/tmp/foo2").st_mode)) == '0640'
        os.unlink( "/tmp/foo2" )
        