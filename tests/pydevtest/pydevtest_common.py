import commands
import json
import os
import psutil
import re
import shlex
import socket
import time


class irods_test_constants(object):
    RUN_IN_TOPOLOGY = False
    RUN_AS_RESOURCE_SERVER = False
    HOSTNAME_1 = HOSTNAME_2 = HOSTNAME_3 = socket.gethostname()


def mod_json_file(fn, new_dict):
    with open(fn) as f:
        env = json.load(f)
    env.update(new_dict)
    with open(fn, 'w') as f:
        json.dump(env, f, indent=4)


def get_hostname():
    return socket.gethostname()


def get_irods_top_level_dir():
    configdir = "/etc/irods/server_config.json"
    topleveldir = "/var/lib/irods"
    if not os.path.isfile(configdir):
        topleveldir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    return topleveldir


def get_irods_config_dir():
    configfile = "/etc/irods/server_config.json"
    configdir = os.path.dirname(configfile)
    if(not os.path.isfile(configfile)):
        configdir = get_irods_top_level_dir() + "/iRODS/config"
    return configdir


def create_directory_of_small_files(directory_name_suffix, file_count):
    if not os.path.exists(directory_name_suffix):
        os.mkdir(directory_name_suffix)
    for i in range(file_count):
        target = open(("%s/%d" % (directory_name_suffix, i)), 'w')
        target.write("iglkg3fqfhwpwpo-" + "A" * i)
        target.close()


def create_local_testfile(filename):
    filepath = os.path.abspath(filename)
    f = open(filepath, 'wb')
    f.write("TESTFILE -- [" + filepath + "]")
    f.close()
    return filepath


def create_local_largefile(filename):
    filepath = os.path.abspath(filename)
    os.system('dd if=/dev/zero of=' + filepath + ' bs=1M count=64')
    return filepath


def check_icmd_outputtype(fullcmd, outputtype):
    allowed_outputtypes = ["LIST", "EMPTY", "ERROR", "", 'STDOUT', 'STDERR', 'STDOUT_MULTILINE', 'STDERR_MULTILINE']
    if outputtype not in allowed_outputtypes:
        print "  full command: [" + fullcmd + "]"
        print "  allowed outputtypes: " + str(allowed_outputtypes)
        print "  unknown outputtype requested: [" + outputtype + "]"
        assert False, "hard fail, bad icommand output format requested"


def getiCmdOutput(mysession, fullcmd):
    parameters = shlex.split(fullcmd)  # preserves quoted substrings
    print "running icommand: " + mysession.getUserName() + "[" + fullcmd + "]"
    if parameters[0] == "iadmin":
        output = mysession.runAdminCmd(parameters[0], parameters[1:])
    else:
        output = mysession.runCmd(parameters[0], parameters[1:])
    # return output array
    #   [0] is stdout
    #   [1] is stderr
    return output


def getiCmdBoolean(mysession, fullcmd, outputtype="", expectedresults="", use_regex=False):
    result = False  # should start as failing, then get set to pass
    parameters = shlex.split(fullcmd)  # preserves quoted substrings
    # expectedresults needs to be a list
    if isinstance(expectedresults, str):  # converts a string to a list
        expectedresults = [expectedresults]
    # get output from icommand
    output = getiCmdOutput(mysession, fullcmd)
    # allow old outputtype identifiers
    if outputtype == "LIST":
        outputtype = "STDOUT"
    elif outputtype == "ERROR":
        outputtype = "STDERR"

    if use_regex:
        regex_msg = 'regex '
    else:
        regex_msg = ''

    # check result listing for expected results
    if outputtype in ['STDOUT', 'STDERR', 'STDOUT_MULTILINE', 'STDERR_MULTILINE']:
        print "  Expecting " + outputtype + ": " + regex_msg + str(expectedresults)
        print "  stdout:"
        print "    | " + "\n    | ".join(output[0].splitlines())
        print "  stderr: [" + output[1].rstrip('\n') + "]"
        # generate lines based on outputtype
        if outputtype in ['STDOUT', 'STDOUT_MULTILINE']:
            lines = output[0].splitlines()
        else:
            lines = output[1].splitlines()
        # look for expected results in the output lines
        if outputtype in ['STDOUT_MULTILINE', 'STDERR_MULTILINE']:
            for er in expectedresults:
                if use_regex:
                    regex_pattern = er
                else:
                    regex_pattern = re.escape(er)
                for line in lines:
                    print '  searching for ' + regex_msg + '[' + er + '] in [' + line.rstrip('\n') + '] ...',
                    if re.search(regex_pattern, line.rstrip('\n')):
                        print "FOUND"
                        break
                    else:
                        print "NOTFOUND"
                else:
                    print "    --> stopping search - expected result not found"
                    break
            else:
                print "    --> stopping search - expected result(s) found"
                result = True
        else:
            for line in lines:
                foundcount = 0
                for er in expectedresults:
                    if use_regex:
                        regex_pattern = er
                    else:
                        regex_pattern = re.escape(er)
                    print '  searching for ' + regex_msg + '[' + er + '] in [' + line.rstrip('\n') + ']...',
                    if re.search(regex_pattern, line.rstrip('\n')):
                        foundcount += 1
                        print "found (" + str(foundcount) + " of " + str(len(expectedresults)) + ")"
                    else:
                        print "NOTFOUND"
                if foundcount == len(expectedresults):
                    print "    --> stopping search - expected result(s) found"
                    result = True
                    break
                else:
                    print "    --> did not find expected result(s)"
    # check that icommand returned no result
    elif (outputtype == "EMPTY" or outputtype == ""):
        print "  Expecting EMPTY output"
        print "  stdout: [" + ",".join(output[0].splitlines()) + "]"
        print "  stderr: [" + output[1].strip() + "]"
        if output[0] == "":
            result = True
    # bad test formatting
    else:
        print "  WEIRD - SHOULD ALREADY HAVE BEEN CAUGHT ABOVE"
        print "  unknown outputtype requested: [" + outputtype + "]"
        assert False, "WEIRD - DUPLICATE BRANCH - hard fail, bad icommand format"
    # return error if stderr is populated unexpectedly
    if outputtype not in ['STDERR', 'STDERR_MULTILINE'] and output[1] != "":
        return False
    # return value
    return result


def assertiCmd(mysession, fullcmd, outputtype="", expectedresults="", use_regex=False):
    ''' Runs an icommand, detects output type, and searches for
    values in expected results list.

    Asserts that this result is correct.

    Returns elapsed runtime.
    '''
    begin = time.time()
    print "\n"
    print "ASSERTING PASS"
    check_icmd_outputtype(fullcmd, outputtype)
    assert getiCmdBoolean(mysession, fullcmd, outputtype, expectedresults, use_regex)
    elapsed = time.time() - begin
    return elapsed


def assertiCmdFail(mysession, fullcmd, outputtype="", expectedresults="", use_regex=False):
    ''' Runs an icommand, detects output type, and searches for
    values in expected results list.

    Asserts that this result is NOT correct.

    Returns elapsed runtime.
    '''
    begin = time.time()
    print "\n"
    print "ASSERTING FAIL"
    check_icmd_outputtype(fullcmd, outputtype)
    assert not getiCmdBoolean(mysession, fullcmd, outputtype, expectedresults, use_regex)
    elapsed = time.time() - begin
    return elapsed


def interruptiCmd(mysession, fullcmd, filename, filesize):
    ''' Runs an icommand, but does not let it complete.

    This function terminates the icommand once filename reaches (>=)
    filesize in bytes.

    Asserts that the icommand was successfully terminated early.

    Returns 0 or -1 or -2.
    '''
    parameters = shlex.split(fullcmd)  # preserves quoted substrings
    print "\n"
    print "INTERRUPTING iCMD"
    print "running icommand: " + mysession.getUserName() + "[" + fullcmd + "]"
    print "  filename set to: [" + filename + "]"
    print "  filesize set to: [" + str(filesize) + "] bytes"
    resultcode = mysession.interruptCmd(parameters[0], parameters[1:], filename, filesize)
    if resultcode == 0:
        print "  resultcode: [0], interrupted successfully"
    elif resultcode == -1:
        print "  resultcode: [-1], icommand completed"
    else:
        print "  resultcode: [-2], icommand timeout"
    assert 0 == resultcode, "0 == resultcode"
    return resultcode


def interruptiCmdDelay(mysession, fullcmd, delay):
    ''' Runs an icommand, but does not let it complete.

    This function terminates the icommand after delay seconds.

    Asserts that the icommand was successfully terminated early.

    Returns 0 or -1.
    '''
    parameters = shlex.split(fullcmd)  # preserves quoted substrings
    print "\n"
    print "INTERRUPTING iCMD"
    print "running icommand: " + mysession.getUserName() + "[" + fullcmd + "]"
    print "  timeout set to: [" + str(delay) + " seconds]"
    resultcode = mysession.interruptCmdDelay(parameters[0], parameters[1:], delay)
    if resultcode == 0:
        print "  resultcode: [0], interrupted successfully"
    else:
        print "  resultcode: [-1], icommand completed"
    assert 0 == resultcode, "0 == resultcode"
    return resultcode


def touch(fname, times=None):
    with file(fname, 'a'):
        os.utime(fname, times)


def cat(fname, string, times=None):
    with file(fname, 'a') as f:
        f.write(string)


def make_file(f_name, f_size, source='/dev/zero'):
    output = commands.getstatusoutput('dd if="' + source + '" of="' + f_name + '" count=1 bs=' + str(f_size))
    if output[0] != 0:
        sys.stderr.write(output[1] + '\n')
        raise OSError(output[0], "call to dd returned non-zero")


def runCmd_ils_to_entries(runCmd_output):
    raw = runCmd_output[0].strip().split('\n')
    collection = raw[0]
    entries = [entry.strip() for entry in raw[1:]]
    return entries


def get_vault_path(session):
    cmdout = session.runCmd("iquest", ["%s", "select RESC_VAULT_PATH where RESC_NAME = 'demoResc'"])
    if cmdout[1] != "":
        raise OSError(cmdout[1], "iquest wrote to stderr when called from get_vault_path()")
    return cmdout[0].rstrip('\n')


def get_vault_session_path(session):
    return os.path.join(get_vault_path(session),
                        "home",
                        session.getUserName(),
                        session.sessionId)


def make_large_local_tmp_dir(dir_name, file_count, file_size):
    os.mkdir(dir_name)
    for i in range(file_count):
        make_file(os.path.join(dir_name, "junk" + str(i).zfill(4)),
                  file_size)
    local_files = os.listdir(dir_name)
    assert len(local_files) == file_count, "dd loop did not make all " + str(file_count) + " files"
    return local_files
