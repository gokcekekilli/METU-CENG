def isValidRow(row:str)->bool:
    for i in range(len(row)):
        if (row[i]=='1'):
            continue
        else:
            return False
    return True
def isValidCol(col:str)->bool:
    for i in range(len(col)):
        if (col[i]=='1'):
            continue
        else:
            return False
    return True
def find_top_left(Pattern:list[str])->list[int]:
    result_tl=[]
    for i in range(len(Pattern)):
        for j in range(len(Pattern[i])):
            if Pattern[i][j]=="1":
                if Pattern[i][j+1]=="1" and Pattern[i+1][j]=="1" and i+1<len(Pattern) and j+1<len(Pattern[0]):
                    result_tl.append([i,j])
    return result_tl
def find_top_right(Pattern:list[str])->list[int]:
    result_tr=[]
    for i in range(len(Pattern)):
        for j in range(len(Pattern[i])):
            if Pattern[i][j]=="1":
                if Pattern[i][j-1]=="1" and Pattern[i+1][j]=="1" and i+1<len(Pattern):
                    result_tr.append([i,j])
    return result_tr
def find_bottom_left(Pattern:list[str])->list[int]:
    result_bl=[]
    for i in range(len(Pattern)):
        for j in range(len(Pattern[i])):
            if Pattern[i][j]=="1":
                if Pattern[i][j+1]=="1" and Pattern[i-1][j]=="1" and j+1<len(Pattern[0]):
                    result_bl.append([i,j])
    return result_bl
def find_bottom_right(Pattern:list[str])->list[int]:
    result_br=[]
    for i in range(len(Pattern)):
        for j in range(len(Pattern[i])):
            if Pattern[i][j]=="1":
                if Pattern[i][j-1]=="1" and Pattern[i-1][j]=="1":
                    result_br.append([i,j])
    return result_br
def contain_zero(tl:list[int], tr:list[int], bl:list[int], br:list[int],Pattern:list[str])->bool:
    for i in range(tl[1]+1,tr[1]):
        for j in range(tl[0]+1,bl[0]):
            if Pattern[i][j]=="0":
                return True
    return False


def count_rectangles(Pattern: list[str])->int:
    count=0
    result_tl=find_top_left(Pattern)
    result_tr=find_top_right(Pattern)
    result_bl=find_bottom_left(Pattern)
    result_br=find_bottom_right(Pattern)
    for tl in result_tl:
        for tr in result_tr:
            for bl in result_bl:
                for br in result_br:
                    if tl[0]==tr[0] and tl[1]<tr[1] and bl[0]==br[0] and bl[1]<br[1] and tl[1]==bl[1] and tl[0]<bl[0] and tr[1]==br[1] and tr[0]<br[0]:
                        left_col=[Pattern[i][tl[1]] for i in range(tl[0],bl[0])]
                        right_col=[Pattern[j][tr[1]] for j in range(tr[0],br[0])]
                        if isValidRow(Pattern[tl[0]][tl[1]:tr[1]]) and isValidRow(Pattern[bl[0]][bl[1]:br[1]]) and isValidCol(left_col) and isValidCol(right_col):
                            if (contain_zero(tl,tr,bl,br,Pattern)):
                                count+=1
    return count
P = [
 "0000000000",
 "0111111000",
 "0100001000",
 "0101111110",
 "0111111010",
 "0001011110",
 "0001000010",
 "0001000010",
 "0001111110",
 "0000000000",
 ]
print(count_rectangles(P))

                                      
    
    


