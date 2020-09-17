from collections import Counter
from string import ascii_uppercase

from utils.cryptography.analyze import ngrams, replace_by_monogram_frequency, replace_by_dict, repeats

s = [
    "C{~%Q%DC?~!C%!&+MD<}CMD~X>MH&",
    "{%N~#~‡!!>C{}!=‡BCD%>D&}!%D›%L#~H>!=}!=C>%{>?‡H›!>DC{~D<+%D?",
    "~DX}C{%LCM##>D<@>M<C~!%!@~%<&LC%HX%DCH}?#LL~C>MCC>%&N%!C%=‡}!]",
    "<~~#D‡~@{‡L%<&=%}C~DLLM@{%!}!&}N}&M%HL‡%C~&}!{}L%D?@{%}D{}L?",
    "M=>+%H‡+D>C{}!=><C{~D>M!&C%#H‡#~+>D~",
    "{}?}LC>#‡L~‡!}!%!›@}D@M}C>++}N‡>DL}B?}H~L%?><=C{‡L~",
    "{}HHL}+›>M=>%CC{~D}={CC}?~%+C~D&}!!~D#MC?D{~%C{@H}+++>D?",
    "L%L}!=MH%D@>!CD%LCC>{}L%#>&~%<&LC›H~>+H}N}!={~}L%&%D]L]}!",
    "<‡&=}QL›}!%LQ~@C}!&D~LL%!&?%!<~DL%=~<CH~?%!C{%C}L%L?M@{%=‡!CH‡?%",
    "<%L?%!›%@>M!CD›LEM}D‡D%C{~DLH>N‡!H›Q‡D{%QL›‡C!>CH>>]}!=%?}LLX}C{{}L!",
    "‡=H}=~<@~#~@%ML~{~{%L%!~D~@C%!&{%<&L>?~+}=MD‡%<&D%C{‡D?",
    ">D>L~Q>LL}#H›L>?~Q‡>QH~?}={CLMLQ‡@C{}?>+%&~=D~~>+M!&~D#D~&QD}&~}",
    "{%N‡%L›?Q%C{~C}@@{>D&X}C{}!C{%CC‡HHL?~}C}L!>C{}!=>+C{~L>DC}]!>X#›}!LC}",
    "<@C{}LD~L~DN~LQD}!=L+D>?%<%N~DL}><C>L{>X›&}LQH%›L>++‡~H}<=C>?",
    "%!}+~LC%C}>!L>+?MCM%H]}!&H}<~LL{~HHH>N~%!&",
    "{%C‡‡EM%HH›M<&~D@>N~D%!&~LC‡~?}C%LQ~@}~L>+}?Q~DC}",
    "<‡!@~C>#~H>N~&>D{%C~&%=%}<"
]
s = ''.join(s)
print(s)

table = {
    'C': 't',
    '{': 'h',
    '~': 'e',
    '%': 'a',
    'Q': 'p',
    'D': 'r',
    '?': 'm',
    '!': 'n',
    '&': 'd',
    '+': 'f',
    'M': 'u',
    '<': 'n',
    '}': 'i',
    'X': 'w',
    '>': 'o',
    'H': 'l',
    'N': 'v',
    '#': 'b',
    '‡': 'e',
    'B': 'x',
    '=': 'g',
    '›': 'y',
    'L': 's',
    '@': 'c',
    ']': 'k',
    'E': 'q',
}
print(len(table))
print(replace_by_dict(s, table))
# for letter in sorted(set(ascii_uppercase) - set(s)):
#     for c in s:
#         if not c.isalpha():
#             s = s.replace(c, letter)
#             break
# print(s, '\n')
#
#
# for i in range(1, 5):
#     print(ngrams(s, i))
# print(repeats(s))
# print()
# # print(replace_by_monogram_frequency(s))
# table = {
#     'C': 't',
#     'A': 'h',
#     'F': 'e',
#
#     'R': 'i',
#     'J': 'n',
#
#     'V': 'g',  # ing
#
#     'D': 'r',  # ther
#
#     'G': 'a',  # freq, and
#     'K': 'd',
#
#     'X': 'w',  # with
#
#     'S': 'o',  # freq, noth
#
#     'L': 's',  # freq, repeats
#
#     'W': 'y',  # ordinary
#
#     'H': 'l',  # freq (mono), repeats
#
#     'T': 'b',  # as belonging to
#
#     'O': 'f',  # repeats
#
#     'Q': 'p',  # display
#
#     'I': 'm',  # manifestations
#
#     'M': 'u',  # you, out, mug, round
#
#     'P': 'n',  # furniture
#
#     'N': 'v',  # have
#
#     'U': 'e',  # I guess it's not one-to-one, (would have been nothing extraordinary)
#     'B': 'x',
#
#     'Y': 'c',  # countenance
#
#     # text from Wuthering Heights
# }
# s2 = replace_by_dict(s, table)
# print(s2, '\n')
# for i in range(1, 5):
#     print(ngrams(s2, i))
# print(repeats(s2))
# print()