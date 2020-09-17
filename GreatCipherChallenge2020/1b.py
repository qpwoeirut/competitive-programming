from utils.cryptography.analyze import ngrams, replace_by_dict

s = "PIKXHMIKUWADXFEWFEDPPXWENHPHEJKAHEHJXPXMVPADBJABASGKFJEYSFJXAMCXLAPJXCCKJAXMIHEJYGYFKGYMXLXKHJKAHJXHHESSEPEQXDYMEMHJKUXDHJKPIKASAUMXVIPWADMXFJXMHKJFAFHARJEMPADYGFXHESXDBIKDHMKCFSMKQXDHSSEKHSALAUBJAXGJAYSXSKPCSXPWADYVIUUKPPXJAPIGYGFXSRUEDPJIFJEXUJEHMKVWAJQKPADCKXMIPEXSVDHAQRJADHFSIKUXDXMXDQXBFKSPEUISFKAMXVHEDHWKMCFXHEJAWKJXFJKHYMXWWKMCXSAWEHIKGEXPIKDEKHYSAWECPADDHAQFXLKWXMFEDXDDHKGWXDHBJAHHAIZJAFJEJQKHHXRMEWSSEWPEJAXUJXFAPXMPADKHFJEPPXJAPIGPADKHHPIBPAFEWADJXLABFEDHAYSBJKMHPKKHHSXCJXXGPVEDMXVFEDJKAHUJAHPAFXDHYHSEMKYEWPADBJAMIFBJARXDHKHPPXMFFEJEYGFKKDHDBAJRCKMIKJKDXDHKHJXPAMFJEXJIHMKCXSGEMXSKHEXFEWFEDXDXMXDQJKHYMXWJAXFEMHJAYSMXWMKCJXXGFEDPEUISWEASSAQMAPXHEWAHJAYSMESIUAHMEVXMXQPHXJJXGXDHWKDQDHAQYSAWECEFXLASJMIKGBJKSCKRSEQHMKDPEJADHAQ"
s = s[::-1]
# print(s, '\n')
# for i in range(1, 5):
#     print(ngrams(s, i))
# print()
# print(replace_by_monogram_frequency(s))

table = {
    'H': 't',
    'D': 'h',
    'X': 'e',

    'A': 'i',
    'J': 'n',

    'Q': 'w',  # within

    'K': 'o',  # tion

    'M': 'r',  # er

    'P': 's',  # his

    'E': 'a',  # freq mono

    'W': 'm',  # amil
    'S': 'l',

    # text from Pride and Prejudice
    'R': 'k',
    'C': 'f',
    'B': 'g',
    'G': 'b',
    'I': 'u',
    'L': 'v',
    'F': 'd',
    'Y': 'y',
    'V': 'p',
    'U': 'c',
    'Z': 'q',
    'N': 'j'
}
s = replace_by_dict(s, table)

print(s, '\n')
# for i in range(1, 5):
#     print(ngrams(s, i))

table['O'] = 'x'
table['T'] = 'z'
alphabet = ""
for c in range(ord('A'), ord('Z') + 1):
    alphabet += table[chr(c)]
print(alphabet)